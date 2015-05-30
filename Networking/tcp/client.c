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
	fd=socket(AF_INET,SOCK_STREAM,0);

	hostptr=gethostbyname("debian");
	memset((void*)&serveraddr,(int)'\0', sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
	serveraddr.sin_port=htons((u_short)PORT);

	connect(fd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));

	gets(msg);
	write(fd, msg, 128);

	read(fd, buffer, 128);
	printf("buffer: %s\n", buffer);
	
	close(fd);
	return 0;
}
