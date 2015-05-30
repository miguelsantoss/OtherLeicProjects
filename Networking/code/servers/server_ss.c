#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define PORT 59000
#define NG 4
#define OFF 0
#define ON 1

const int PERM = 0666;

char* itoa_n(int num, char* str, int base);

int main() {
	int fd, fd_ret, newfd, errorreq = 1, erroraws = 1, size_file_up, clientlen, dontreply = 0, posbuffer, auxpos = 0, size_file_ret, i;
	char buffer[1024];
	char msg[1024];
	char *data, *filename, *size_file_c_up, *size_file_c_ret;
	char* c;
	char* c_ret;
	char* auxsize;
	char* auxname;
	char* filename_ret;
	char* data_ret;
	struct sockaddr_in serveraddr, clientaddr;
	FILE *fp;
	
	fd=socket(AF_INET,SOCK_STREAM,0);
	memset((void*)&serveraddr,(int)'\0', sizeof(serveraddr));
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons((u_short)PORT);
	
	if((bind(fd,(struct sockaddr*)&serveraddr, sizeof(serveraddr))) == -1) exit(1);
	
	listen(fd,5);
	
	while(1){
		clientlen=sizeof(clientaddr);
		
		if(newfd=accept(fd,(struct sockaddr*)&clientaddr, &clientlen) == -1) exit(1);
		
		read(newfd, buffer, sizeof(buffer));

		if(!strncmp(buffer, "REQ\n", 4)) {
			errorreq = 0;
			strcpy(msg,"REP "); 
	 		//If everything's ok, the SS will send the file.
	 		//Else, the SS returns an error message.
		    	filename = buffer + 4;
		    	fp = fopen(filename,"r");
			if (fp == NULL)
				dontreply = 1;
				strcat(msg, "nok");
			if (dontreply = 0) {	
				strcat(msg, "ok");					    	
				fseek(fp, 0, SEEK_END);
			    	while((*c = fgetc(fp)) != EOF) {
			    		strcat(data, c);
				}
				size_file_up = ftell(fp);
				sprintf(size_file_c_up, "%d", size_file_up);
			    	strcat(msg, size_file_c_up);
			    	strcat(msg, data);
				write(newfd, msg, sizeof(msg));
			}
		}
		else if (errorreq == 1) {
			strcpy(msg,"REP "); 	
			strcat(msg, "ERR");
			write(newfd, msg, sizeof(msg));	
		}
		else if(!strncmp(buffer, "UPS\n", 4)) {
			erroraws = 0;
			//If everythings ok, the SS will reply with 'ok'. 
			//Else, the SS returns an error message.
			posbuffer = 4;
			while(buffer[posbuffer] != ' ') {
				auxname[auxpos] = buffer[posbuffer];
				auxname++;
				posbuffer++;
			}
			strcpy(filename_ret, auxname);
			posbuffer++;
			//FIXME
			//Condition if the filename_ret is NULL: nok or ERR?
			while(buffer[posbuffer] != ' ') {
				auxsize[auxpos] = buffer[posbuffer];
				auxsize++;
				posbuffer++;
			}
			size_file_ret = (int)strtol(auxsize, NULL, 10);
	    	if (size_file_ret == 0) {
	    		strcpy(msg, "AWS ");
	    		strcat(msg, "nok ");
			}
			else if(size_file_ret != 0) {
				for(i = posbuffer; i == posbuffer + size_file_ret; i++) {
					*c = buffer[i];
					strcat(data_ret, c);
				}
				fd_ret = open(filename_ret, O_RDWR | O_CREAT, PERM);
				write(fd_ret, data_ret, sizeof(data_ret));
				strcpy(msg, "AWS");
				strcat(msg, "ok");
				write(newfd, msg, sizeof(msg));	
			}
		}
		else if (erroraws == 1) {
			strcpy(msg,"AWS "); 	
			strcat(msg, "ERR");	
			write(newfd, msg, sizeof(msg));
		}
	}
	close(fd); 
	close(newfd);
	return 0;
}


