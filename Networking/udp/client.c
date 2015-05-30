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

	hostptr=gethostbyname("debian");
	memset((void*)&serveraddr,(int)'\0', sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
	serveraddr.sin_port=htons((u_short)PORT);

	addrlen=sizeof(serveraddr);

	gets(buffer);
	sendto(fd,buffer,strlen(buffer)+1,0, (struct sockaddr*)&serveraddr,addrlen);

	addrlen=sizeof(serveraddr);

	recvfrom(fd,msg,sizeof(msg),0, (struct sockaddr*)&serveraddr,&addrlen);
	printf("msg: %s\n", msg);

	close(fd);
	return 0;
}
