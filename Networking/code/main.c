#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sring.h>
#define PORT 58004

int main () {
    char option[128], CSname[128], CSport[128];
    scanf(option);
    
    switch (option):
        case 'user':
            scanf(CSname);
            scanf(CSport);
    launch_user_interface(CSname, CSport);
        case 'CS':
            scanf(CSport);
    launch_cs_interface(CSport);
        case 'SS':
            scanf(CSport);
    launch_ss_interface(CSport);
    
    return 0;
}