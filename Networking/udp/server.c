#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#define PORT 59000

int main() {
	int fd;
	struct hostent *hostptr;
	struct sockaddr_in serveraddr, clientaddr;
	int addrlen;
	char buffer[128];
	char msg[128];
	fd=socket(AF_INET,SOCK_DGRAM,0);

	memset((void*)&serveraddr,(int)'\0', sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons((u_short)PORT);

	bind(fd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));

	addrlen=sizeof(clientaddr);

	recvfrom(fd,buffer,sizeof(buffer),0, (struct sockaddr*)&clientaddr, &addrlen);
	printf("buffer: %s\n", buffer);

	gets(msg);
	sendto(fd,msg,strlen(msg)+1,0, (struct sockaddr*)&clientaddr,addrlen);

	close(fd);
	return 0;
}
