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
    char *key;
    KV_t *Vector;
    int Ncliente;
    int status;
    int terminou;
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

sem_t * Escrita;
sem_t *Clients;
sem_t *Servers;
pthread_mutex_t *LockClients, *LockServers;
pthread_t *Server;
Buffer Buff;
pthread_mutex_t LockKos;
Kos KOS;
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
    for(indice = 0; indice < HashSize;indice++)
        *(HashTable + indice) = NULL;
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
        newBuffer[i].terminou = 0;
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

int GetValue(Shard ShardN,int ShardIndice,char *key,char *save)
{
    int indice = hash(key);
    KosVector ShardAux;
    if(!(ShardN[ShardIndice].KosHashTable[indice]))
        return -1;
    ShardAux = ShardN[ShardIndice].KosHashTable[indice];
    while(ShardAux && strcmp(ShardAux->key_value->key,key))
          ShardAux = ShardAux->next;
    if(ShardAux){
        strcpy(save,ShardAux->key_value->value);
        return 0;
    }

    return -1;
}

// funcao get que verifica as condicoes dos argumentos e lanca o GetValue
void get_server(int ncliente)
{
pthread_mutex_lock(&LockKos);

    if(!Buff[ncliente].key)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid >= KOS->ShardsLength)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid < KOS_ZERO)
        Buff[ncliente].status = -1;
    if( Buff[ncliente].status != -1)
        Buff[ncliente].status = GetValue(KOS->KosShard,Buff[ncliente].shardid,Buff[ncliente].key,Buff[ncliente].value); 
    sem_post(&Escrita[ncliente]);
    
pthread_mutex_unlock(&LockKos);
}

/*
----------------------
Funcao cliente:
----------------------
*/


// Funcao do cliente que recebe os argumentos e espera pelos servidores e kos para escrever no cliente
char* kos_get(int clientid,int shardId,char *key)
{
    pthread_mutex_lock(&LockClients[clientid]);
    sem_wait(&Clients[clientid]);
    delay();
    char * value = (char *)malloc(sizeof(char) * 20);
    Buff[clientid].status = 0;
    Buff[clientid].key = (char *)malloc(sizeof(char *) * KV_SIZE);  
    Buff[clientid].value = (char *)malloc(sizeof(char *) * KV_SIZE);
    Buff[clientid].FuncaoResponsavel = 1;
    strcpy(Buff[clientid].key,key);
    Buff[clientid].shardid = shardId;
    sem_post(&Servers[clientid]);
    sem_wait(&Escrita[clientid]);
    if(Buff[clientid].status == -1)
    {
        pthread_mutex_unlock(&LockClients[clientid]);
        return NULL;
    }
    strcpy(value,Buff[clientid].value);
    pthread_mutex_unlock(&LockClients[clientid]);
    return value;
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
int PutKeyValue(Shard ShardN,int ShardIndice,char *key,char *value,char *save)
{
    int indice = hash(key);
    KosVector KeyValue = NewKeyValue(key,value);
    KosVector ShardAux;
    if(!(ShardN[ShardIndice].KosHashTable[indice])){
        ShardN[ShardIndice].NumberElements++;
        ShardN[ShardIndice].KosHashTable[indice] = KeyValue;
        return -1;
    }
  if(!strcmp(ShardN[ShardIndice].KosHashTable[indice]->key_value->key,key)){
        strcpy(save,ShardN[ShardIndice].KosHashTable[indice]->key_value->value);
        strcpy(ShardN[ShardIndice].KosHashTable[indice]->key_value->value,value);
        free(KeyValue);
        return 0;
    }
  ShardAux = ShardN[ShardIndice].KosHashTable[indice];
  while(ShardAux->next)
    {
        if(!strcmp(ShardAux->key_value->key,key))
        {
            strcpy(save,ShardAux->key_value->value);
            strcpy(ShardAux->key_value->value,value);
            free(KeyValue);
            return 0;
        }
        ShardAux = ShardAux->next;
    }

	       if(!strcmp(ShardAux->key_value->key,key))
        {
            strcpy(save,ShardAux->key_value->value);
            strcpy(ShardAux->key_value->value,value);
            free(KeyValue);
            return 0;
        }
    ShardN[ShardIndice].NumberElements++;
    ShardAux->next = KeyValue;
    return -1;
}

// Funcao que verifica as condicoes dos argumentos e lanca o PutValue
void put_server(int ncliente)
{
pthread_mutex_lock(&LockKos);
    
    if(!Buff[ncliente].key)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid >= KOS->ShardsLength)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid < KOS_ZERO)
        Buff[ncliente].status = -1;
    if( Buff[ncliente].status != -1)
        Buff[ncliente].status = PutKeyValue(KOS->KosShard,Buff[ncliente].shardid,Buff[ncliente].key,Buff[ncliente].value,Buff[ncliente].value);
    sem_post(&Escrita[ncliente]);   
pthread_mutex_unlock(&LockKos);
}


/*
----------------------
Funcao cliente:
----------------------
*/
// funcao do cliente que permite colocar no KOS e espera que o servidor permita devolver o valor alterado ao cliente
char* kos_put(int clientid,int shardId,char *key,char *value)
{
    pthread_mutex_lock(&LockClients[clientid]);
    sem_wait(&Clients[clientid]);
    delay();
    char * Value = (char *)malloc(sizeof(char) * 20);
    Buff[clientid].status = 0;
    Buff[clientid].key = (char *)malloc(sizeof(char *) * KV_SIZE);  
    Buff[clientid].value = (char *)malloc(sizeof(char *) * KV_SIZE);
    Buff[clientid].FuncaoResponsavel = 0;
    Buff[clientid].shardid = shardId;
    strcpy(Buff[clientid].key,key);
    strcpy(Buff[clientid].value,value);

    sem_post(&Servers[clientid]);
    sem_wait(&Escrita[clientid]);
        if(Buff[clientid].status == -1)
    {
        pthread_mutex_unlock(&LockClients[clientid]);
        return NULL;
    }
    strcpy(Value,Buff[clientid].value);
    pthread_mutex_unlock(&LockClients[clientid]);
    return Value;
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
int RemoveKeyValue(Shard ShardN,int ShardIndice,char *key,char *save) 
{ 
    
    int indice = hash(key); 
    KosVector ShardAux; 
    KosVector ShardAuxNext;
    if(indice == -1)
        return -1;
    if(!(ShardN[ShardIndice].KosHashTable[indice])){
    
        return -1;
    }
    if(!strcmp(ShardN[ShardIndice].KosHashTable[indice]->key_value->key,key)) 
    {
        ShardN[ShardIndice].NumberElements--;
        strcpy(save,ShardN[ShardIndice].KosHashTable[indice]->key_value->value);
        ShardAux = ShardN[ShardIndice].KosHashTable[indice]; 
        ShardN[ShardIndice].KosHashTable[indice] = ShardN[ShardIndice].KosHashTable[indice]->next; 
        free(ShardAux); 
        
       return 0; 
    } 
    ShardAux = ShardN[ShardIndice].KosHashTable[indice]; 
    ShardAuxNext = ShardN[ShardIndice].KosHashTable[indice]->next; 
    while(ShardAuxNext)
    { 
        if(!strcmp(ShardAuxNext->key_value->key,key)){
            ShardN[ShardIndice].NumberElements--;
            strcpy(save,ShardAuxNext->key_value->value);
            ShardAux->next = ShardAuxNext->next; 
            free(ShardAuxNext); 
        
            return 0; 
        } 
        ShardAux = ShardAux->next; 
        ShardAuxNext = ShardAuxNext->next; 
    } 
	if(!strcmp(ShardAuxNext->key_value->key,key)){
            ShardN[ShardIndice].NumberElements--;
            strcpy(save,ShardAuxNext->key_value->value);
            ShardAux->next = NULL;
            free(ShardAuxNext); 
        
            return 0; 
        } 
    
    return -1;
} 

//Funcao a ser chamada pelas tarefas clientes, para remover uma chave do kos
void remove_server(int ncliente)
{
pthread_mutex_lock(&LockKos);   
    if(!Buff[ncliente].key)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid >= KOS->ShardsLength)
        Buff[ncliente].status = -1;
    if(Buff[ncliente].shardid < KOS_ZERO)
        Buff[ncliente].status = -1;
    if( Buff[ncliente].status != -1)
        Buff[ncliente].status = RemoveKeyValue(KOS->KosShard,Buff[ncliente].shardid,Buff[ncliente].key,Buff[ncliente].value);
    sem_post(&Escrita[ncliente]);
pthread_mutex_unlock(&LockKos);

}


/*
----------------------
Funcao cliente:
----------------------
*/

//Funcao a ser chamada pelas tarefas clientes, para remover uma dada chave do kos
char * kos_remove(int clientid,int shardId, char *key)
{
    pthread_mutex_lock(&LockClients[clientid]);
    sem_wait(&Clients[clientid]);
    delay();
    char *value = (char *)malloc(sizeof(char) * KV_SIZE);
    Buff[clientid].status = 0;
    Buff[clientid].key = (char *)malloc(sizeof(char *) * KV_SIZE);  
    Buff[clientid].value = (char *)malloc(sizeof(char *) * KV_SIZE);
    Buff[clientid].FuncaoResponsavel = 2;
    Buff[clientid].shardid = shardId;
    strcpy(Buff[clientid].key,key);
    sem_post(&Servers[clientid]);
    sem_wait(&Escrita[clientid]);
    if(Buff[clientid].status == -1)
    {
        pthread_mutex_unlock(&LockClients[clientid]);
        return NULL;
    }
    strcpy(value,Buff[clientid].value);
    pthread_mutex_unlock(&LockClients[clientid]);
    return value;
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
    for(HashTableIndice = 0, VectorIndice = 0;HashTableIndice < HT_SIZE;HashTableIndice++)
        if(ShardN[NumberShard].KosHashTable[HashTableIndice])
            VectorIndice = PutVector(ShardN,NumberShard,HashTableIndice,Vector_kos,VectorIndice);
}

//Funcao auxiliar que verifica todos os argumentos e chama a funcao getkeys
void kos_GetAllKeys(int clientid)
{
    
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
    pthread_mutex_lock(&LockKos);
    kos_GetAllKeys(ncliente);
    sem_post(&Escrita[ncliente]);
    pthread_mutex_unlock(&LockKos);
}

/*
----------------------
Funcao cliente:
----------------------
*/

//Funcao invocada pela tarefa cliente, de modo a obter todas as chaves
KV_t * Kos_getAllKeys(int clientid,int shardId,int *dim)
{
    pthread_mutex_lock(&LockClients[clientid]);
    sem_wait(&Clients[clientid]);
    delay();
    KV_t *vect;
    dim = (int *)malloc(sizeof(int));
    Buff[clientid].status = 0;
    Buff[clientid].FuncaoResponsavel = 3;
    Buff[clientid].shardid = shardId;
    sem_post(&Servers[clientid]);
    sem_wait(&Escrita[clientid]);
    if(Buff[clientid].status == -1)
    {
        *dim = -1;
        pthread_mutex_unlock(&LockClients[clientid]);
        return NULL;
    }

    *dim = Buff[clientid].dim;
    vect = Buff[clientid].Vector;
    pthread_mutex_unlock(&LockClients[clientid]);
    return vect;
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
  while(1){
    pthread_mutex_lock(&LockServers[ClienteID]);
    sem_wait(&Servers[ClienteID]);
    if(Buff[ClienteID].terminou == 1)
        break;
    if(Buff[ClienteID].FuncaoResponsavel == 0)
        put_server(ClienteID);
    if(Buff[ClienteID].FuncaoResponsavel == 1)
        get_server(ClienteID);
    if(Buff[ClienteID].FuncaoResponsavel == 2)
        remove_server(ClienteID);
    if(Buff[ClienteID].FuncaoResponsavel == 3)
        GetKeys_server(ClienteID);
    
    sem_post(&Clients[ClienteID]);

    pthread_mutex_unlock(&LockServers[ClienteID]);
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
  int i;
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
  Buff = NewBuffer(buf_size);
 Escrita = (sem_t *)malloc(sizeof(sem_t) * number_server_threads);
  Server = (pthread_t *)malloc(sizeof(pthread_t) * number_server_threads);
    if (!Server) return -1;
  for(i = 0; i < number_server_threads;i++)
  {
    sem_init(&Escrita[i],0,0);
    sem_init(&Clients[i],0,1);
    sem_init(&Servers[i],0,0);
    pthread_mutex_init(&LockClients[i],NULL);
    pthread_mutex_init(&LockServers[i],NULL);
  }
    servers_init(number_server_threads);
  pthread_mutex_init(&LockKos,NULL);
  return 0;
}

