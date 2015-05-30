#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

#include <kos_client.h>
#include <delay.h>
#include <hash.h>

#define HT_SIZE 10
#define KOS_ZERO 0


/* 
**********************************************************

Estruturas

**********************************************************

*/

typedef struct buffer
{
    int FuncaoResponsavel;
    int dim;
    int shardid;
    char *value;
		char *resposta;
    char *key;
    KV_t *Vector;
    int status;
	int ocupado;
	sem_t sem1;
} *Buffer;

typedef struct KosElemento {
		
    KV_t *key_value;
    struct KosElemento *next;
} *KosVector;

typedef struct shard{
    KosVector *KosHashTable;
    int NumberElements;

} *Shard;

typedef struct kos{
    Shard KosShard;
    int ShardsLength;
} *Kos;


/* 
**********************************************************

Variaveis globais

**********************************************************

*/

pthread_rwlock_t **LeitoresEscritores;
sem_t ClienteTarefa;
sem_t ServidoraTarefa;
pthread_mutex_t MutexBuffer;
sem_t * Escrita;
sem_t *Clients;
sem_t *Servers;
pthread_mutex_t *LockClients, *LockServers, *LockKos;
pthread_t *Server;
Buffer Buff;
Kos KOS;
int Buf_size;
int *Ids;


/* 
**********************************************************

Funcoes para inicializar o kos 

**********************************************************

*/

/*
----------------------
Funcoes auxiliares:
----------------------
*/


// Cria uma hashtable vazia

KosVector * NewHashTable(int HashSize)
{
    int indice;
    KosVector * HashTable = (KosVector *)malloc(sizeof(KosVector) * HashSize);
    for(indice = 0; indice < HashSize;indice++){
        *(HashTable + indice) = NULL;	
		
	}
    return HashTable;
}

// Cria o KOS com um numero de shards e inicializa as hashtables de cada shard
Kos NewKos(int Shardslength)
{
    Kos KOS = (Kos)malloc(sizeof(struct kos));
    int i;
    KOS->KosShard = (Shard )malloc(sizeof(struct shard) * Shardslength);
    for(i = 0; i < Shardslength;i++){
        KOS->KosShard[i].KosHashTable = NewHashTable(HT_SIZE);
        KOS->KosShard[i].NumberElements = 0;
    }
    KOS->ShardsLength = Shardslength;
    return KOS;
}


// cria um KV_t com valores

KV_t* SetKeyValue(KosVector KeyValue,char *key,char *value)
{
    KV_t *KV_vect = (KV_t *)malloc(sizeof(KV_t));
    strcpy(KV_vect->key,key);
    strcpy(KV_vect->value,value);
    return KV_vect;
}


// Cria um Vector que e uma lista ligada de KV_t 
KosVector NewKeyValue(char* key,char *value)
{
    KosVector KeyValue = (KosVector)malloc(sizeof(struct KosElemento));
    KeyValue->next = NULL;
    KeyValue->key_value = SetKeyValue(KeyValue,key,value);
    return KeyValue;
}


// inicializa o buffer
Buffer NewBuffer(int tamanho)
{
    Buffer newBuffer = (Buffer)malloc(sizeof(struct buffer) * tamanho);
    int i;
    for(i = 0; i< tamanho;i++)
    {
        newBuffer[i].key = (char *)malloc(sizeof(char *) * KV_SIZE);    
        newBuffer[i].value = (char *)malloc(sizeof(char *) * KV_SIZE);
    }
    return newBuffer;
}




/*
**********************************************************

    Funcoes para o kos_get, incluindo auxiliares:

**********************************************************
*/


/*
----------------------
Funcoes auxiliares:
----------------------
*/


//procura numa determinada shard a chave e retorna o valor dela

int GetValue(Shard ShardN,int ShardIndice,char *key,int ncliente)
{
    int indice = hash(key);
    KosVector ShardAux;
	pthread_rwlock_rdlock(&LeitoresEscritores[ShardIndice][indice]);
    if(!(ShardN[ShardIndice].KosHashTable[indice])){
		pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
        return -1;
	}
    ShardAux = ShardN[ShardIndice].KosHashTable[indice];
    while(ShardAux && strcmp(ShardAux->key_value->key,key))
          ShardAux = ShardAux->next;
    if(ShardAux){
        strcpy(Buff[ncliente].resposta,ShardAux->key_value->value);
		pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
        return 0;
    }
	pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
    return -1;
}

// funcao get que verifica as condicoes dos argumentos e lanca o GetValue
void get_server(int ncliente)
{
	ncliente = ncliente % Buf_size;
    if(!Buff[ncliente].key)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid >= KOS->ShardsLength)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid < KOS_ZERO)
        Buff[ncliente].status = -1;
    if( Buff[ncliente].status != -1)
        Buff[ncliente].status = GetValue(KOS->KosShard,Buff[ncliente].shardid,Buff[ncliente].key,ncliente); 
   
}

/*
----------------------
Funcao cliente:
----------------------
*/


// Funcao do cliente que recebe os argumentos e espera pelos servidores e kos para escrever no cliente
char* kos_get(int clientid,int shardId,char *key)
{
	clientid = clientid % Buf_size;
     sem_wait(&ServidoraTarefa);
	int i;
	pthread_mutex_lock(&MutexBuffer);
  	for(i = 0; i < Buf_size;i++){
		
		if(Buff[i].ocupado == 0){
			clientid = i;
			Buff[i].ocupado = 1;
			break;
		}
	}
	pthread_mutex_unlock(&MutexBuffer);
  
    Buff[clientid].status = 0;
    Buff[clientid].resposta = (char *)malloc(sizeof(char *) * KV_SIZE);
    Buff[clientid].FuncaoResponsavel = 1;
    strcpy(Buff[clientid].key,key);
    Buff[clientid].shardid = shardId;
  	Buff[clientid].ocupado = 2;
    sem_post(&ClienteTarefa);
    sem_wait(&Buff[clientid].sem1);
    if(Buff[clientid].status == -1)
    {
    	Buff[clientid].ocupado=0;
		sem_post(&ServidoraTarefa);
		return NULL;
    }
	Buff[clientid].ocupado=0;
	sem_post(&ServidoraTarefa);	
    return Buff[clientid].resposta;
}


/*
**********************************************************

Funcoes para o kos_put, incluindo auxiliares:

**********************************************************
*/

/*
----------------------
Funcoes auxiliares:
----------------------
*/

//Funcao que vai a um determinado shard colocar o valor e a chave caso a chave exista guarda no buffer 
int PutKeyValue(Shard ShardN,int ShardIndice,char *key,char *value,int ncliente)
{
    int indice = hash(key);
		pthread_rwlock_wrlock(&LeitoresEscritores[ShardIndice][indice]);
    KosVector KeyValue = NewKeyValue(key,value);
    KosVector ShardAux;
    if(!(ShardN[ShardIndice].KosHashTable[indice])){// nao existe nada
        ShardN[ShardIndice].NumberElements++;
        ShardN[ShardIndice].KosHashTable[indice] = KeyValue;
        
		pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
        return -1;
    }
	 ShardAux = ShardN[ShardIndice].KosHashTable[indice];
  if(!strcmp(ShardAux->key_value->key,key)){// existe e e igual so altera o valor
        strcpy(Buff[ncliente].resposta,ShardAux->key_value->value);
        strcpy(ShardAux->key_value->value,value);
        free(KeyValue);
			pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
        return 0;
    }
 
  while(ShardAux->next)
    {
        if(!strcmp(ShardAux->key_value->key,key))// 
        {
            strcpy(Buff[ncliente].resposta,ShardAux->key_value->value);
            strcpy(ShardAux->key_value->value,value);
            free(KeyValue);
						pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
            return 0;
        }
        ShardAux = ShardAux->next;
    }

	       if(!strcmp(ShardAux->key_value->key,key))
        {
            strcpy(Buff[ncliente].resposta,ShardAux->key_value->value);
            strcpy(ShardAux->key_value->value,value);
            free(KeyValue);
						pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
            return 0;
        }
    ShardN[ShardIndice].NumberElements++;
    ShardAux->next = KeyValue;
		pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
    return -1;
}

// Funcao que verifica as condicoes dos argumentos e lanca o PutValue
void put_server(int ncliente)
{
    ncliente = ncliente % Buf_size;
    if(!Buff[ncliente].key)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid >= KOS->ShardsLength)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid < KOS_ZERO)
        Buff[ncliente].status = -1;
    if( Buff[ncliente].status != -1)
        Buff[ncliente].status = PutKeyValue(KOS->KosShard,Buff[ncliente].shardid,Buff[ncliente].key,Buff[ncliente].value,ncliente);
    
}


/*
----------------------
Funcao cliente:
----------------------
*/

// 0 vazio 1 cliente a preencher 2 pronto servidor 3 servidor a tratar 4 pronto cliente 
// funcao do cliente que permite colocar no KOS e espera que o servidor permita devolver o valor alterado ao cliente
char* kos_put(int clientid,int shardId,char *key,char *value)
{
   
	clientid = clientid % Buf_size;
    sem_wait(&ServidoraTarefa);
	int i;
	pthread_mutex_lock(&MutexBuffer);
  	for(i = 0; i < Buf_size;i++){
		
		if(Buff[i].ocupado == 0){
			clientid = i;
			Buff[i].ocupado = 1;
			break;
		}
	}
	pthread_mutex_unlock(&MutexBuffer);
    Buff[clientid].status = 0;  
    Buff[clientid].resposta = (char *)malloc(sizeof(char *) * KV_SIZE);
    Buff[clientid].FuncaoResponsavel = 0;
    Buff[clientid].shardid = shardId;
    strcpy(Buff[clientid].key,key);
    strcpy(Buff[clientid].value,value);
	Buff[clientid].ocupado = 2;
    sem_post(&ClienteTarefa);
    sem_wait(&Buff[clientid].sem1);
    if(Buff[clientid].status == -1)
    {
    	Buff[clientid].ocupado=0;
		sem_post(&ServidoraTarefa);
		return NULL;
    }
	Buff[clientid].ocupado=0;
	sem_post(&ServidoraTarefa);	
    return Buff[clientid].resposta;
}


/*
**********************************************************

    Funcoes para o kos_remove, incluindo auxiliares:

**********************************************************
*/

/*
----------------------
Funcoes auxiliares:
----------------------
*/

//Funcao auxiliar para a remocao de chaves do sistema de ficheiros 
int RemoveKeyValue(Shard ShardN,int ShardIndice,char *key,int ncliente) 
{ 
    
    int indice = hash(key); 
		pthread_rwlock_wrlock(&LeitoresEscritores[ShardIndice][indice]);
    KosVector ShardAux; 
    KosVector ShardAuxNext;
    if(indice == -1)
        return -1;
    if(!(ShardN[ShardIndice].KosHashTable[indice])){
    			pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
        return -1;
    }
    if(!strcmp(ShardN[ShardIndice].KosHashTable[indice]->key_value->key,key)) 
    {
        ShardN[ShardIndice].NumberElements--;
        strcpy(Buff[ncliente].resposta,ShardN[ShardIndice].KosHashTable[indice]->key_value->value);
        ShardAux = ShardN[ShardIndice].KosHashTable[indice]; 
        ShardN[ShardIndice].KosHashTable[indice] = ShardN[ShardIndice].KosHashTable[indice]->next; 
        free(ShardAux); 
       pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
       	return 0; 
    } 
    ShardAux = ShardN[ShardIndice].KosHashTable[indice]; 
    ShardAuxNext = ShardN[ShardIndice].KosHashTable[indice]->next; 
    while(ShardAuxNext)
    { 
        if(!strcmp(ShardAuxNext->key_value->key,key)){
            ShardN[ShardIndice].NumberElements--;
            strcpy(Buff[ncliente].resposta,ShardAuxNext->key_value->value);
            ShardAux->next = ShardAuxNext->next; 
            free(ShardAuxNext); 
        	pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
            return 0; 
        } 
        ShardAux = ShardAux->next; 
        ShardAuxNext = ShardAuxNext->next; 
    } 
	pthread_rwlock_unlock(&LeitoresEscritores[ShardIndice][indice]);
    return -1;
} 

//Funcao a ser chamada pelas tarefas clientes, para remover uma chave do kos
void remove_server(int ncliente)
{
	ncliente = ncliente % Buf_size;
    if(!Buff[ncliente].key)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid >= KOS->ShardsLength)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid < KOS_ZERO)
        Buff[ncliente].status = -1;
    if( Buff[ncliente].status != -1)
        Buff[ncliente].status = RemoveKeyValue(KOS->KosShard,Buff[ncliente].shardid,Buff[ncliente].key,ncliente);
    
}


/*
----------------------
Funcao cliente:
----------------------
*/

//Funcao a ser chamada pelas tarefas clientes, para remover uma dada chave do kos
char * kos_remove(int clientid,int shardId, char *key)
{
    
	clientid = clientid % Buf_size;
    sem_wait(&ServidoraTarefa);
	int i;
	pthread_mutex_lock(&MutexBuffer);
  	for(i = 0; i < Buf_size;i++){
		
		if(Buff[i].ocupado == 0){
			clientid = i;
			Buff[i].ocupado = 1;
			break;
		}
	}
	pthread_mutex_unlock(&MutexBuffer);
    Buff[clientid].status = 0;
   
    Buff[clientid].resposta = (char *)malloc(sizeof(char *) * KV_SIZE);
    Buff[clientid].FuncaoResponsavel = 2;
    Buff[clientid].shardid = shardId;
    strcpy(Buff[clientid].key,key);
   	Buff[clientid].ocupado = 2;
    sem_post(&ClienteTarefa);
    sem_wait(&Buff[clientid].sem1);
    if(Buff[clientid].status == -1)
    {
    	Buff[clientid].ocupado=0;
		sem_post(&ServidoraTarefa);
		return NULL;
    }
	Buff[clientid].ocupado=0;
	sem_post(&ServidoraTarefa);	
    return Buff[clientid].resposta;
}

/*
**********************************************************

    Funcoes para o kos_getAllkeys, incluindo auxiliares:

**********************************************************
*/

/*
----------------------
Funcoes auxiliares:
----------------------
*/

//funcao que faz o set do par key value no vecctor a apresentar ao cliente
int VectorKos(KV_t * Vector_kos,int VectorIndice,char * key,char * value)
{
    strcpy(Vector_kos[VectorIndice].value,value);
    strcpy(Vector_kos[VectorIndice].key,key);
    VectorIndice++;
    return VectorIndice;
}

// Funcao que percorre um determinado indice da shard e que chama a funcao VectorKos
int PutVector(Shard ShardN,int ShardIndice,int HashTableIndice, KV_t *Vector_kos,int VectorIndice)
{
    KosVector VectorAux = ShardN[ShardIndice].KosHashTable[HashTableIndice];
    while(VectorAux)
    {
        VectorIndice = VectorKos(Vector_kos,VectorIndice,VectorAux->key_value->key,VectorAux->key_value->value);
        VectorAux = VectorAux->next;
    }
    return VectorIndice;
}

// Funcao auxiliar que percorre todos os indices da hard e chama o putvector
void getkeys(Shard ShardN,int NumberShard,KV_t * Vector_kos)
{
    int HashTableIndice ,VectorIndice;
    for(HashTableIndice = 0, VectorIndice = 0;HashTableIndice < HT_SIZE;HashTableIndice++){
		pthread_rwlock_rdlock(&LeitoresEscritores[NumberShard][HashTableIndice]);     
	   if(ShardN[NumberShard].KosHashTable[HashTableIndice])
            VectorIndice = PutVector(ShardN,NumberShard,HashTableIndice,Vector_kos,VectorIndice);
		pthread_rwlock_unlock(&LeitoresEscritores[NumberShard][HashTableIndice]);
	}
}

//Funcao auxiliar que verifica todos os argumentos e chama a funcao getkeys
void GetAllKeys(int clientid)
{
    clientid = clientid % Buf_size;
    int shardId = Buff[clientid].shardid;
    if(KOS->KosShard[shardId].NumberElements == 0)
        Buff[clientid].status = -1;
    if(shardId >= KOS->ShardsLength)
        Buff[clientid].status = -1;
    if(shardId < KOS_ZERO)
        Buff[clientid].status = -1;
    if(Buff[clientid].status != -1)
    {
        Buff[clientid].Vector = (KV_t *)malloc(sizeof(KV_t) * KOS->KosShard[shardId].NumberElements);
        getkeys(KOS->KosShard,Buff[clientid].shardid,Buff[clientid].Vector);
        Buff[clientid].dim = KOS->KosShard[shardId].NumberElements;
        Buff[clientid].status = 0;
    }

}

//Funcao chamada pelas tarefas servidoras, para obter o vector com as chaves do kos
void GetKeys_server(int ncliente)
{
    ncliente = ncliente % Buf_size;
    GetAllKeys(ncliente);
   
}

/*
----------------------
Funcao cliente:
----------------------
*/

//Funcao invocada pela tarefa cliente, de modo a obter todas as chaves
KV_t * kos_getAllKeys(int clientid,int shardId,int *dim)
{
		clientid = clientid % Buf_size;
        sem_wait(&ServidoraTarefa);
	int i;
	pthread_mutex_lock(&MutexBuffer);
  	for(i = 0; i < Buf_size;i++){
		
		if(Buff[i].ocupado == 0){
			clientid = i;
			Buff[i].ocupado = 1;
			break;
		}
	}
	pthread_mutex_unlock(&MutexBuffer);
    Buff[clientid].status = 0;
    Buff[clientid].FuncaoResponsavel = 3;
    Buff[clientid].shardid = shardId;
     	Buff[clientid].ocupado = 2;
    sem_post(&ClienteTarefa);
    sem_wait(&Buff[clientid].sem1);
    if(Buff[clientid].status == -1)
    {
        *dim = -1;
      Buff[clientid].ocupado=0;
	sem_post(&ServidoraTarefa);		
        return NULL;
    }
    *dim = Buff[clientid].dim;
	Buff[clientid].ocupado=0;
	sem_post(&ServidoraTarefa);	
    return Buff[clientid].Vector;
}

/*
**********************************************************

    Inicializacao do kos e tarefas servidoras

**********************************************************
*/


/*
------------------------------
    Funcao da thread servidora
------------------------------
*/

//Funcao a ser corrida pelas threads servidoras
void * ServerThread(void *arg)
{
	  int ClienteID = *(int *)arg;
	ClienteID = ClienteID % Buf_size;
  while(1){
  
    sem_wait(&ClienteTarefa);
	int i;
	pthread_mutex_lock(&MutexBuffer);
  	for(i = 0; i < Buf_size;i++){
		
		if(Buff[i].ocupado == 2){
			ClienteID = i;
			Buff[i].ocupado = 3;
			break;
		}
	}
	pthread_mutex_unlock(&MutexBuffer);
    if(Buff[ClienteID].FuncaoResponsavel == 0)
        put_server(ClienteID);
    else if(Buff[ClienteID].FuncaoResponsavel == 1)
        get_server(ClienteID);
    else if(Buff[ClienteID].FuncaoResponsavel == 2)
        remove_server(ClienteID);
    else if(Buff[ClienteID].FuncaoResponsavel == 3)
        GetKeys_server(ClienteID);
    sem_post(&Buff[ClienteID].sem1);
    

  }
    return NULL;
}

// Ciclo de criacao das tarefas servidoras
void servers_init(number_server_threads) {
    int i, s;
    for(i = 0; i<number_server_threads; i++){
        Ids[i]=i;
        if ((s = pthread_create(&Server[i], NULL, &ServerThread, &(Ids[i]))) != 0) {
            printf("pthread_create failed with code %d!\n", s);
        }
    }
}

/*
----------------------
Funcao principal:
----------------------
*/

//Inicia o sistema de ficheiros e as threads servidoras
int kos_init(int number_server_threads,int buf_size,int num_shards)
{ 
  int i,j;
  Ids = (int *)malloc(sizeof(int) * number_server_threads);
    if (!Ids) return -1;
  Clients = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
    if (!Clients) return -1;
  Servers = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
    if (!Servers) return -1;
  KOS = NewKos(num_shards);
  LockClients = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_server_threads);
    if (!LockClients) return -1;
  LockServers = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_server_threads);
    if (!LockServers) return -1;
  LockKos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_shards * 10);
  LeitoresEscritores = (pthread_rwlock_t **)malloc(sizeof(pthread_rwlock_t*) * num_shards);
  for(j =0 ;j < num_shards;j++){
		LeitoresEscritores[j] = (pthread_rwlock_t *)malloc(sizeof(pthread_rwlock_t) * 10);
		for(i = 0; i < 10;i++)
			pthread_rwlock_init(&LeitoresEscritores[j][i],NULL);	
	}

    if (!LockKos) return -1;
  Buff = NewBuffer(buf_size);
  Buf_size = buf_size;
  Escrita = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
  Server = (pthread_t *)malloc(sizeof(pthread_t) * number_server_threads);
    if (!Server) return -1;

  sem_init(&ServidoraTarefa,0,buf_size);
  sem_init(&ClienteTarefa,0,0);
  for(i = 0; i < number_server_threads;i++)
  {
    sem_init(&Escrita[i],0,0);
    sem_init(&Clients[i],0,1);
    sem_init(&Servers[i],0,0);
    pthread_mutex_init(&LockClients[i],NULL);
    pthread_mutex_init(&LockServers[i],NULL);
  }
  servers_init(number_server_threads);
  for(i = 0; i < num_shards;i++)
  {
    pthread_mutex_init(&LockKos[i],NULL);
  }
  return 0;
}


/*

void escreverFicheiro(int ShardID, char* key, char *value){
		char* key_f = (char*)malloc(char)*20);
		char* value_f = (char*)malloc(char)*20);
		char* numel = (char*)malloc(char)*11);
		char* primeiro = (char*)malloc(char)*21);
		sprintf(key_f, "%s", key);
		sprintf(value_f, "%s", value);
		for (i=0, i<20, i++){
				if(key_f[i]!='\0'){
					sprintf(key_f, "%s ", key_f);
				}
		}
		for (i=0, i<20, i++){
				if(value_f[i]!='\0'){
					sprintf(value_f, "%s ", value_f);
				}
		}
		fseek(file[i], 0, SEEK_END);
		fwrite(key_f, 1, 20, file[i]);
		fwrite(value_f, 1, 20, file[i]);
		fwrite('\n', 1, 1, files[i]);
		fseek(file[i], 0, SEEK_SET);
		sprintf(numel, "%d", KOS->KosShard[ShardID].NumberElements);
		for (i=0, i<11, i++){
				if(numeli]!='\0'){
					sprintf(numel, "%d ", numel);
				}
		}
		fseek(file[i],0, SEEK_SET);
		sprintf(primeiro, "- %s NPKV -\n", numel);
		fwrite(primeiro, 1, 11, file[i]);
		KOS->KosShard[ShardID].NumberElements ++;
}

void escreverFicheiroValue(int ShardID, char* key, char *value){
		char* key_f = (char*)malloc(char)*20);
		char* value_f = (char*)malloc(sizeof(char)*20);
		char* numel = (char*)malloc((sizeof(char)*11);
		char* fich = (char*)malloc(sizeof(char)*20);
		sprintf(key_f, "%s", key);
		sprintf(value_f, "%s", value);
		for (i=0, i<20, i++){
				if(key_f[i]!='\0'){
					sprintf(key_f, "%s ", key_f);
				}
		}
		for (i=0, i<20, i++){
				if(value_f[i]!='\0'){
					sprintf(value_f, "%s ", value_f);
				}
		}
		fseek(file[i], 21, SEEK_SET);
		for (i=0, i<  KOS->KosShard[ShardID].NumberElements, i++){
			fread(fich, 1, 20, file[ShardID]);
			if (strcmp(fich, key_f)==0){
				fwrite(value_f, 1, 20, file[SharID];
				return;
			}
			fseek(file[ShardID], 21, SEEK_CUR);
		}
}
		
void remove(int ShardID, char* key){
		char* key_f = (char*)malloc(sizeof(char)*20);
		char* value_f = (char*)malloc(sizeof(char)*20);
		char* numel = (char*)malloc(sizeof(char)*11);
		char* espacobranco = (char*)malloc(sizeof(char)*40);
		sprintf(key_f, "%s", key);
		sprintf(value_f, "%s", value);
		for (i=0, i<20, i++){
				if(key_f[i]!='\0'){
					sprintf(key_f, "%s ", key_f);
				}
		}
		for (i=0, i<20, i++){
				if(value_f[i]!='\0'){
					sprintf(value_f, "%s ", value_f);
				}
		}
		fseek(file[i], 21, SEEK_SET);
		sprintf(espacobranco, "                                        ",);
		for (i=0, i<  KOS->KosShard[ShardID].NumberElements, i++){
			bzero(fich);
			fread(fich, 1, 20, file[ShardID]);
		
			
			if (strcmp(fich, key_f)==0){
				fseek(file[ShardID], -20, SEEK_CUR);
				fwrite(espacobranco, 1, 40, file[SharID];
				fwrite('\n', 1,1, file[SharID];
				fseek(file[i],0, SEEK_SET);
				sprintf(numel, "%d", KOS->KosShard[ShardID].NumberElements);
				sprintf(primeiro, "- %s NPKV -\n", numel);
				fwrite(primeiro, 1, 11, file[i]);
		
				return;
			}
			fseek(file[ShardID], 21, SEEK_CUR);
		}
		
		
}		


char* tratamento( char *fileKV){
	int i=0; int tamanho=0;
	for (i=0; i<20; i++){
		if(fileKV[i]!=' '){
			tamanho ++;
		}
	}
	char* tratada = (char*)malloc(sizeof(char)*tamanho);
	for(i=0;i<tamanho;i++){
		tratada[i]=fileKV[i];
	}
	return tratada;
}

void leFicheiro(FILE **file,char nome[]){
		int ShardID;
		int i;
		int ic;
		char *shardid;
		char* fileKey = (char*)malloc(sizeof(char)*20);
		char* fileValue = (char*)malloc(sizeof(char)*20);
		char* linha;
		char *key;
		char *value;
		shardid = devolveNumero(nome);
		ShardID = atoi(shardid);
		
		fseek(file[i], 21, SEEK_SET);
		for (ic=0; i<  *KOS->KosShard[ShardID].NumberElements; i++){
			fread(fileKey, 1, 20, file[i]);
			key=tratamento(fileKey);
			fread(fileValue, 1, 20, file[ShardID]);
			value=tratamento(fileValue);
			kos_put(0,key,value);
			fseek(file[ShardID], 1, SEEK_CUR);
		 }
}

Funcao principal:


Inicia o sistema de ficheiros e as threads servidoras

int kos_init(int number_server_threads,int buf_size,int num_shards)
{ 
  int i,j;
  char NomeFicheiro[20];
  Ids = (int *)malloc(sizeof(int) * number_server_threads);
    if (!Ids) return -1;
  Clients = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
    if (!Clients) return -1;
  Servers = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
    if (!Servers) return -1;
  KOS = NewKos(num_shards);
  LockClients = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_server_threads);
    if (!LockClients) return -1;
  LockServers = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_server_threads);
    if (!LockServers) return -1;
  LockKos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_shards * 10);
  LeitoresEscritores = (pthread_rwlock_t **)malloc(sizeof(pthread_rwlock_t*) * num_shards);
  for(j =0 ;j < num_shards;j++){
		LeitoresEscritores[j] = (pthread_rwlock_t *)malloc(sizeof(pthread_rwlock_t) * 10);
		for(i = 0; i < 10;i++)
			pthread_rwlock_init(&LeitoresEscritores[j][i],NULL);	
	}

    if (!LockKos) return -1;
  Buff = NewBuffer(buf_size);
  Buf_size = buf_size;
  Escrita = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
  Server = (pthread_t *)malloc(sizeof(pthread_t) * number_server_threads);
    if (!Server) return -1;

  sem_init(&ServidoraTarefa,0,buf_size);
  sem_init(&ClienteTarefa,0,0);
  for(i = 0; i < number_server_threads;i++)
  {
    sem_init(&Escrita[i],0,0);
    sem_init(&Clients[i],0,1);
    sem_init(&Servers[i],0,0);
    pthread_mutex_init(&LockClients[i],NULL);
    pthread_mutex_init(&LockServers[i],NULL);
  }
  servers_init(number_server_threads);
  for(i = 0; i < num_shards;i++)
  {
    pthread_mutex_init(&LockKos[i],NULL);
  }
  file = (FILE **)malloc(sizeof(FILE *) * num_shards);
  for(i = 0; i < num_shards;i++){
	sprintf(NomeFicheiro, "File%d",i);
	file[i] = fopen(NomeFicheiro,"r+");
	if(file[i] == NULL){file[i] = fopen(NomeFicheiro,"w+"); }
		else{leFicheiro(file, NomeFicheiro);}
	}
		
  return 0;
}
*/
/* esta em comentario porque tem diversos bugs a verificar*/
