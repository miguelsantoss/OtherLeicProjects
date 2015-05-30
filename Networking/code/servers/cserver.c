#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#define PORT 59000
#define NG 4
extern int errno;

int fdTCP, newfdTCP, clientlenTCP, addrlenTCP, fdUDP, addrlenUDP, nfiles, portN, nbyTCP, auxnbyTCP, sizeincFile, i_sizeTCP, i_nfilesUDP, nSSservers, sizeauxincFile, oldestFile = 1, latestFile = 0;
struct sockaddr_in serveraddrTCP, clientaddrTCP, serveraddrUDP, clientaddrUDP;
char optionUDP[128], optionTCP[128], answUDP[128], answTCP[128], auxsize[10], nfiles_strUDP[5], serverName[50], serverPort[10], fileName[20];
char *incFile, *pTCP;
char** IPSS, **ports, **fileList;
pthread_t threadh[2];
FILE *files;

void *TCPserver(void *arg);
void *UDPserver(void *arg);
int search_file_list(char ** List, int nf, char name[]);
int sendFilesSS(char* file, int size, char** ip, char** portss);
void printAllFiles();
void saveinFile();

int main(int argc, char* argv[]) {
	int i;
	FILE *servers;
	servers = fopen("servers","r");
	if (servers == NULL)exit(1);

    	fscanf(servers, "Total Servers: %d", &nSSservers);
	fileList = (char**)malloc(sizeof(char*)*30);
	if (fileList == NULL) exit(1);
	
	IPSS = (char**)malloc(sizeof(char*)*nSSservers);	
	if (IPSS == NULL) exit(1);
	ports = (char**)malloc(sizeof(char*)*nSSservers);	
	if (ports == NULL) exit(1);
	i = 0;
	while (i < nSSservers){
		fscanf(servers, "%d %s %s", &i, serverName, serverPort);
		IPSS[i-1] = (char*)malloc(sizeof(char)*strlen(serverName));
		ports[i-1] = (char*)malloc(sizeof(char)*strlen(serverPort));
		strcpy(IPSS[i-1], serverName);
		strcpy(ports[i-1], serverPort);
	}
	fclose(servers);
	files = fopen("files","r");
	if (files == NULL) {
		files = fopen("files","w");
		if (files == NULL)exit(1);
		fseek(files, 0, SEEK_SET);
		fprintf(files, "Files: 0");
		fseek(files, 13, SEEK_SET);
		fprintf(files, "1");
		fseek(files, 2, SEEK_CUR);
		fprintf(files, 0);
		fseek(files, 0, SEEK_CUR);
		fclose(files);
		files = fopen("files","r");
		if (files == NULL)exit(1);
	}
	fseek(files, 0, SEEK_SET);
	fscanf(files, "Files: %d", &nfiles);
	fseek(files, 13, SEEK_SET);
	fscanf(files, "%d", &oldestFile);
	fseek(files, 2, SEEK_CUR);
	fscanf(files, "%d", &latestFile);
	i = 0;
	fseek(files, 23, SEEK_SET);
	while (i < nfiles){
		fscanf(files, "%d %s", &i, fileName);
		fileList[i-1] = (char*)malloc(sizeof(char)*strlen(fileName));
		strcpy(fileList[i-1], fileName);
		fseek(files, (i+1)*23, SEEK_SET);
	}
	fclose(files);
	if (argc == 3) {
		if (!strcmp(argv[1], "-p")) {
			portN = (int)strtol(argv[2], NULL, 10);
			if (portN == 0) {exit(1);}
		}
	}
	else {
		portN = PORT + NG;
	}
	if (pthread_create (&threadh[0], NULL, TCPserver, NULL) != 0)exit(1);  
	if (pthread_create (&threadh[0], NULL, UDPserver, NULL) != 0)exit(1);
	while(1);
	return 0;
}

void saveinFile() {
	int i = 0;
	files = fopen("files","w");
	fseek(files, 0, SEEK_SET);
	fprintf(files, "Files: %d", nfiles);
	fseek(files, 13, SEEK_SET);
	fprintf(files, "%d", oldestFile);
	fseek(files, 2, SEEK_CUR);
	fprintf(files, "%d", latestFile);
	fseek(files, 0, SEEK_CUR);
	while (i < nfiles) {
		fseek(files, (i+1)*23, SEEK_SET);
		fprintf(files, "%d %s", i+1, fileList[i]);
		fseek(files, 0, SEEK_CUR);
		i++;
	}
	fflush(files);
	fclose(files);
}

int search_file_list(char ** List, int nf, char name[]) {
	int i = 0;
	if (nf == 0) {
		return 0;
	}
	else {
		while(*(List+i) != NULL) {
			if (!strcmp(*(List+i), name)) {
				return 1;
			}
			i++;
		}
		return 0;
	}
}
void printAllFiles() {
	int i = 0;
	while (i < nfiles){
		printf("%d - %s\n", i, fileList[i]);
		i++;
	}
}

int sendFilesSS(char* file, int size, char** ip, char** portss) {
	int i = 0, fd, n, sizeaux = size, nw = 0, j;
	struct hostent *ss;
	struct sockaddr_in addr;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)return 1;
	memset((void*)&addr,(int)'\0', sizeof(addr));
	addr.sin_family=AF_INET;
	while(i < nSSservers) {
		ss = gethostbyname(ip[i]);
		addr.sin_addr.s_addr = ((struct in_addr *)(ss->h_addr_list[0]))->s_addr;
		addr.sin_port=htons((u_short)((int)strtol(portss[i], NULL, 10)));
		n = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
		if (n == -1)return 2;
		while(sizeaux > 0) {
			nw = write(fd, file, sizeaux);
			if (nw <=0)return 3;
			sizeaux -= nw;
			file+=nw;
		}
		file-=size;
		i++;
	}
	close(fd);
	return 4;	
}

void *UDPserver(void *arg) {
	int i;
	if ((fdUDP=socket(AF_INET,SOCK_DGRAM,0))==-1)exit(1);
	memset((void*)&serveraddrUDP,(int)'\0', sizeof(serveraddrUDP));
	serveraddrUDP.sin_family=AF_INET;
	serveraddrUDP.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddrUDP.sin_port=htons((u_short)portN);

	if ((bind(fdUDP,(struct sockaddr*)&serveraddrUDP, sizeof(serveraddrUDP)))==-1)exit(1);

	while(1) {
		addrlenUDP=sizeof(clientaddrUDP);
		if ((recvfrom(fdUDP,optionUDP,sizeof(optionUDP),0, (struct sockaddr*)&clientaddrUDP, &addrlenUDP))==-1)exit(1);
		if (!strncmp(optionUDP, "LST\n", 4)) {
				strcpy(answUDP, "AWL ");
				if (nSSservers == 1) {
					strcat(answUDP, IPSS[0]);
					strcat(answUDP, " ");
					strcat(answUDP, ports[0]);
					strcat(answUDP, " ");
				}
				else {
					srand(time(NULL));
					i = rand() % nSSservers;
					strcat(answUDP, IPSS[i]);
					strcat(answUDP, " ");
					strcat(answUDP, ports[i]);
					strcat(answUDP, " ");
				}
				sprintf(nfiles_strUDP, "%d", nfiles);
				strcat(answUDP, nfiles_strUDP);
				if (nfiles > 0) {
					i_nfilesUDP = 0;
					while (i_nfilesUDP < nfiles) {
						strcat(answUDP, " ");
						strcat(answUDP, *(fileList + i_nfilesUDP));
						i_nfilesUDP++;
					}
				}
				else {
					strcat(answUDP, " ");
					strcat(answUDP, "EOF");
				}
				strcat(answUDP, "\n");
		}
		else {
			strcpy(answUDP, "ERR\n");
		}
		if ((sendto(fdUDP,answUDP,strlen(answUDP)+1,0, (struct sockaddr*)&clientaddrUDP,addrlenUDP))==-1)exit(1);
	}
	close(fdUDP);
}

void *TCPserver(void *arg) {
	int i;
	if ((fdTCP=socket(AF_INET,SOCK_STREAM,0))==-1)exit(1);

	memset((void*)&serveraddrTCP,(int)'\0', sizeof(serveraddrTCP));
	serveraddrTCP.sin_family=AF_INET;
	serveraddrTCP.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddrTCP.sin_port=htons((u_short)portN);

	if ((bind(fdTCP,(struct sockaddr*)&serveraddrTCP, sizeof(serveraddrTCP)))==-1)exit(1);
	listen(fdTCP,5);

	while(1) {
		memset(optionTCP, '\0', sizeof(optionTCP));
		memset(answTCP, '\0', sizeof(answTCP));
		clientlenTCP=sizeof(clientaddrTCP);
		if ((newfdTCP=accept(fdTCP,(struct sockaddr*)&clientaddrTCP, &clientlenTCP))==-1)exit(1);
		auxnbyTCP = 1;
		while(!(auxnbyTCP = read(newfdTCP, optionTCP, 128))) {if (auxnbyTCP==-1)exit(1);}
		if (!strncmp(optionTCP, "UPR ", 4)) { 
			pTCP = optionTCP + 4;
			if (strlen(pTCP) > 21) {
				strcpy(answTCP, "ERR\n");
				nbyTCP = 4;
			}
			else {
				if (pTCP[strlen(pTCP)-1] != '\n') {
					strcpy(answTCP, "ERR\n");
					nbyTCP = 4;
				}
				else {
					pTCP[strlen(pTCP)-1] = '\0';
					if (!search_file_list(fileList, nfiles, pTCP)) {
						strcpy(answTCP, "AWR new\n");
						nbyTCP = 8;
						if (nfiles < 30) {
							fileList[nfiles] = (char*)malloc(sizeof(char)*strlen(pTCP));
							strcpy(fileList[nfiles], pTCP);
							nfiles++;
							latestFile++;
						}
						else {
							i = strlen(fileList[oldestFile-1]);
							free(fileList[oldestFile-1]);
							fileList[oldestFile-1] = (char*)malloc(sizeof(char)*strlen(pTCP));
							strcpy(fileList[oldestFile-1], pTCP);
							oldestFile++;
							latestFile++;
							if (oldestFile > 30) {
								oldestFile = 1;
							}
						}
						printAllFiles();
					}
					else {
						strcpy(answTCP, "AWR dup\n");
						nbyTCP = 8;
					}
				}
			}
		}
		else if (!strncmp(optionTCP, "UPC ", 4)) { 
			pTCP = optionTCP + 4; 
			i_sizeTCP = 0;
			while(pTCP[i_sizeTCP] != ' ') {
				auxsize[i_sizeTCP] = pTCP[i_sizeTCP];
				i_sizeTCP++;
			}
			auxsize[i_sizeTCP] = '\0';
			i_sizeTCP++;
			pTCP+=i_sizeTCP;
			sizeincFile = (int)strtol(auxsize, NULL, 10);
			if (sizeincFile == 0) {
				strcpy(answTCP, "ERR\n");
				nbyTCP = 4;				
			}
			else if (sizeincFile > 5000000) {
				strcpy(answTCP, "ERR\n");
				nbyTCP = 4;
			}
			else if (nfiles  == 0) {
				strcpy(answTCP, "ERR\n");
				nbyTCP = 4;
			}
			else if (latestFile == 0) {
				strcpy(answTCP, "ERR\n");
				nbyTCP = 4;
			}
			else {
				i = strlen(fileList[latestFile-1]);
				incFile = (char*)malloc(sizeof(char)*(sizeincFile+strlen(auxsize)+6+i));
				if (incFile == NULL) {
					strcpy(answTCP, "ERR\n");
					nbyTCP = 4;
				}
				else {
					strcpy(incFile, "UPS ");
					strcat(incFile, fileList[latestFile-1]);
					strcat(incFile, " ");
					strcat(incFile, auxsize);
					strcat(incFile, " ");
					sizeauxincFile = sizeincFile - (strlen(optionTCP) - i_sizeTCP - 4);
					strcat(incFile, pTCP);
					if (sizeincFile > 128 - i_sizeTCP - 4) {
						while(sizeauxincFile > 0) {
							while(!(auxnbyTCP = read(newfdTCP, optionTCP, 128))) {if (auxnbyTCP==-1)exit(1);}
							sizeauxincFile -= auxnbyTCP;
							strcat(incFile, optionTCP);
							memset(optionTCP, '\0', sizeof(optionTCP));
						}
					}
					strcpy(answTCP, "AWR ok\n");
					nbyTCP = 7;
					if (sizeincFile != (strlen(incFile)-(strlen(auxsize)+7+i))) {
						strcpy(answTCP, "ERR\n");
						nbyTCP = 4;
					}
					else {
						i = sendFilesSS(incFile, (sizeincFile+strlen(auxsize)+6+i), IPSS, ports);
						free(incFile);
						incFile = NULL;
					}
				}
			}
		}
		else { 
			strcpy(answTCP, "ERR\n");
			nbyTCP = 4;
		}
		while (nbyTCP > 0) {
			if ((auxnbyTCP = write(newfdTCP, answTCP, 128))==-1)exit(1);
			nbyTCP -= auxnbyTCP;
		}
		close(newfdTCP);
		saveinFile();
		
	}
	close(fdTCP); 
}