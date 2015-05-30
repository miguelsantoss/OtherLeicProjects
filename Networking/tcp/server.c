#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#define PORT 59000

int main() {
	int fd, newfd, clientlen;
	struct hostent *hostptr;
	struct sockaddr_in serveraddr, clientaddr;
	int addrlen;
	char buffer[128];
	char msg[128];
	fd=socket(AF_INET,SOCK_STREAM,0);

	memset((void*)&serveraddr,(int)'\0',
	sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons((u_short)PORT);

	bind(fd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));

	listen(fd,5);

	clientlen=sizeof(clientaddr);

	newfd=accept(fd,(struct sockaddr*)&clientaddr, &clientlen);
	read(newfd, buffer, 128);
	printf("buffer: %s\n", buffer);
	gets(msg);
	write(newfd, msg, 128);
	close(fd); 
	close(newfd);
	return 0;
}
