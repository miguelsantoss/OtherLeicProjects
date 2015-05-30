#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define PORT 58000
#define NG 4
#define ON 1
#define OFF 0
#define HOST_TEST "tejo.ist.utl.pt"
#define HOST_PORT 58011
#define MSG_SIZE 1024
#define FNAME_SIZE 20
#define TOTAL_SS 10
#define COMMAND_SIZE 8
#define CODE_UDP_01 "FD ERROR: UDP'S SOCKET FAILED"
#define CODE_TCP_01 "FD ERROR: TCP'S SOCKET FAILED"
#define CODE_TCP_02 "ERROR TCP: IP NOT VALID"
#define CODE_TCP_03 "ERROR TCP: PORT NOT VALID"
#define CODE_USER_01 "EXIT APPLICATION: USER'S CHOICE"
#define CODE_SIZE_01 "RETRIEVE FAILED: FILE'S SIZE SMALLER THAN EXPECTED"
#define CODE_SIZE_02 "RETRIEVE FAILED: FILE'S SIZE BIGGER THAN EXPECTED"
#define CODE_LIST_01 "ERROR CS: FIELDS INVALID"
#define CODE_LIST_02 "ERROR CS: NUMBER OF FILES EXCEEDS PERMITED"
#define CODE_LIST_03 "ERROR CS: FILE NAME SIZE TOO BIG"
#define CODE_LIST_04 "ERROR CS: NUMBER OF FILE NAMES SENT INCORRECT"
#define CODE_RET_01 "ERROR SS: FIELD NOK DETECTED"
#define CODE_RET_02 "ERROR SS: FIELD STATUS REPORTS ERROR"
#define CODE_RET_03 "ERROR SS: RETRIEVE ANSWER NOT VALID"
#define CODE_UPD_01 "ERROR CS: DUPLICATED FILE"
#define CODE_UPD_02 "ERROR CS: WRONG FORM REQUEST"
#define CODE_UPD_03 "ERROR CS: CS ANSWER IS NOT VALID"
#define CODE_UPD_04 "ERROR CS: FILE TRANSFER INCOMPLETE"
#define CODE_UPD_05 "ERROR CS: SINTAX ERROR IN PROTOCOL"
#define CODE_FILE_01 "ERROR FILE: FILE DOES NOT EXIST"
#define CODE_CMD_01 "ERROR INPUT: NO VALID OPTION"


void exit_user(char* message);
char* itoa_n(int num, char* str, int base);
void reverse_n(char str[], int length);
void upload_content(char* file_name);
char* retrieve_content(char* file_name);
char* list_contents();
int myAtoi(char *str);
void process_file(char* ss_answer_raw, char* file_name);
void process_list(char* cs_answer);


// Protocols' variables
int fdUDP, fdTCP;
struct hostent *hostptrUDP, *hostptrTCP;
struct sockaddr_in serveraddrUDP, clientaddrUDP, serveraddrTCP, clientaddrTCP;
int addrlen;
int portN;
int portL;
//char* Port_ext;
char* IP_ext;
int portSS_n = 0;
char host_local[128];

FILE *fp;

// Main program

int main (int argc, char* argv[]) {
    
    // User's interface's variables
    char* option = (char*)malloc(sizeof(char) * MSG_SIZE);
    char* file_name = (char*)malloc(sizeof(char) * FNAME_SIZE);
    char* servers_answer;
    
    // Filling the requirements
    if (argc == 3) {
        if (!strcmp(argv[1], "-p")) {
            portN = (int)strtol(argv[2], NULL, 10);
            if (portN == 0) { exit(1); }
        }
    }
    else {
        portN = PORT + NG;
    }
    gethostname(host_local,128);
    printf("\nClient's information:\n");
    printf("Host: %s\n", host_local);
    printf("Port: %d\n\n", portN);
    
    printf("Central Server's Information:\n");
    printf("Host: %s\n", HOST_TEST);
    printf("Port: %d\n\n", HOST_PORT);
    
    // Client's interface
    printf("Client's interface is ready.\n");
    while(1) {
        printf("Enter an option, please: ");
        scanf("%s", option);
        getchar();
        if (!strcmp(option, "list")) {
            servers_answer = list_contents();
            process_list(servers_answer);
        }
        else if (!strcmp(option, "retrieve")) {
            scanf("%s", file_name);
            servers_answer = retrieve_content(file_name);
            process_file(servers_answer, file_name);
        }
        else if (!strcmp(option, "upload")) {
            scanf("%s", file_name);
            upload_content(file_name);
        }
        else if (!strcmp(option, "exit")) {
            exit_user(CODE_USER_01);
            return 0;
        }
        else {
            printf("%s\n", CODE_CMD_01);
            printf("\nPlease, try again.\n");
        }
    }
    return 0;
}

void exit_user(char* message) {
    // Depending on the message, we should terminate the program in a different way, reporting the error to the user
    printf("%s\n", message);
	exit(1);
}

char* list_contents() {
    char cmd[4];
    char msg[1024];
    char* c;
    
    // Initializing UDP
    fdUDP = socket(AF_INET,SOCK_DGRAM, 0);
    if(fdUDP == -1) { exit_user(CODE_UDP_01); }
    
    hostptrUDP = gethostbyname(HOST_TEST);
    memset((void*)&serveraddrUDP,(int)'\0', sizeof(serveraddrUDP));
    serveraddrUDP.sin_family = AF_INET;
    serveraddrUDP.sin_addr.s_addr = ((struct in_addr *)(hostptrUDP->h_addr_list[0]))->s_addr;
    serveraddrUDP.sin_port = htons((u_short)HOST_PORT);
    
    addrlen = sizeof(serveraddrUDP);

    // Sends the request for 'list' to the CS, namely LST.
    
    strncpy(cmd,"LST\n", 4);
	if(( sendto(fdUDP,cmd,strlen(cmd) + 1,0, (struct sockaddr*)&serveraddrUDP,addrlen)) == -1) exit(1); 
    
    // Recieves the answer from the CS, a string with the SS servers all sorted.
    addrlen=sizeof(serveraddrUDP);
    recvfrom(fdUDP,msg,sizeof(msg),0, (struct sockaddr*)&serveraddrUDP,&addrlen);
    
    close(fdUDP);
    // Checks if it's the correct answer
    if(!strncmp("AWL", msg, 3)) {
        return msg;
    }
    else {
        exit_user(CODE_LIST_01);
        return msg;
    }
}

void process_list(char* cs_answer) {
    char* IPSS = (char*)malloc(sizeof(char) * MSG_SIZE);
    char* portSS = (char*)malloc(sizeof(char) * MSG_SIZE);
    char* number_files = (char*)malloc(sizeof(char) * MSG_SIZE);
    char* c;
    int  number_files_n, i, j, counter_files, files_name_checker, file_number = 1;
    IP_ext = (char*)malloc(sizeof(char)*16);
    c = cs_answer;
    c += 4;
    for(j = 0; *(c) != ' '; j++, c++){
        IPSS[j] = *(c);
    }
    c++;
    for(j = 0; *(c) != ' '; j++, c++){
        portSS[j] = *(c);
    }
    c++;
    for(j = 0; *(c) != ' '; j++, c++){
        number_files[j] = *(c);
    }
    strcpy(IP_ext, IPSS);
    portSS_n = myAtoi(portSS);
    number_files_n = myAtoi(number_files);
    
    // Checks if the number of files is in the valid range
    if(number_files_n > 30) {
        exit_user(CODE_LIST_02);
        return;
    }
    
    // Checks if the number of files is correct and the size of the names
    for(c++, files_name_checker = 0, counter_files = 0; *(c) != '\n'; c++) {
        if(*(c) == ' ' || *(c) == '\n'){
            counter_files++;
            if(files_name_checker > 20) {
                exit_user(CODE_LIST_03);
                return;
            }
            else {
                files_name_checker = 0;
            }
        }
        files_name_checker++;
    }
	if(number_files_n > 0) {counter_files++;}
    if(counter_files != number_files_n) {
        exit_user(CODE_LIST_04);
        return;
    }
    
    c = cs_answer;
	c += 7 + strlen(IPSS) + strlen(portSS) + strlen(number_files);
	printf("\nNearest SS server:\n\nIP: %s\nPort: %d\n\nNumber of files: %d\nList of files:\n", IPSS, portSS_n , number_files_n);
    
    // Prints each files name to the user
    printf("%d ", file_number);
	file_number++;
    for (; *(c) != '\n'; c++) {
        if( *(c) == ' ') {
            printf("\n%d ", file_number);
			file_number++;
        }
        else {
            printf("%c",*(c));
        }
    }
    printf("\n");
    printf("-------------------\n");
}

char* retrieve_content(char* file_name) {
    char cmd[COMMAND_SIZE + FNAME_SIZE];
    char msg[5000000];
    int auxnbyTCP = 1;
    int auxncmd = 0;
    int n_write;

//    if(IP_ext == NULL) { exit_user(CODE_TCP_02); }
    if(portSS_n == 0) { exit_user(CODE_TCP_03); }
    
    // Initializing TCP
    fdTCP=socket(AF_INET,SOCK_STREAM,0);
    if(fdTCP == -1) { exit_user(CODE_TCP_01); }
    
    hostptrTCP = gethostbyname(HOST_TEST);
    memset((void*)&serveraddrTCP,(int)'\0', sizeof(serveraddrTCP));
    serveraddrTCP.sin_family = AF_INET;
    serveraddrTCP.sin_addr.s_addr = inet_addr(IP_ext);
    serveraddrTCP.sin_port = htons((u_short)portSS_n);
    
    connect(fdTCP,(struct sockaddr*)&serveraddrTCP, sizeof(serveraddrTCP));
    
    // Writes the request for 'retrieve' to the CS, namely REQ.
    strcpy(cmd,"REQ ");
    strcat(cmd, file_name);
    strcat(cmd, "\n");
    auxncmd = 4 + strlen(file_name) + 2;
    
    while(auxncmd > 0) {
        if((n_write = write(fdTCP,cmd,strlen(cmd))) == -1) exit(1);
        auxncmd -= n_write;
    }
    
    // Reads the answer, a string with the syntax "REP status size data"
    while(!(auxnbyTCP = read(fdTCP,msg,sizeof(msg)))) {
        if (auxnbyTCP==-1)exit(1);
    }

    close(fdTCP);
    
    // Checks the status if it's correct
    if(!strncmp("REP ok", msg, 6)) {
        return msg;
    }
    else if (!strncmp("REP nok", msg, 7)) {
        exit_user(CODE_RET_01);
        return msg;
       }
    else if (!strncmp("ERR", msg, 3)) {
        exit_user(CODE_RET_02);
        return msg;
    }
    else {
        exit_user(CODE_RET_03);
        return msg;
    }
}

void process_file(char* ss_answer_raw, char* file_name) {
    char* c = ss_answer_raw;
    char* rest;
    char* size_file = (char*)malloc(sizeof(char)*16);
    int size_file_n = 0, counter = 0, i;
    
    c += 4;

    // Jumps the status field
    for(; *(c) != ' '; c++){
    }
    c++;
    
    // Reads the size of the file
    for(i = 0; c[i] != ' '; i++){
	size_file[i] = c[i];
    }
    
	size_file[i] = '\0';
    
	c+=strlen(size_file);
    size_file_n = myAtoi(size_file);
    
    // Opens the file
    fp = fopen(file_name,"w");
    if(fp == NULL) { exit(1); }
    
    if(!fp) {
        exit_user(CODE_FILE_01);
    }
    
    // Writes on the new file the number of bytes
	rest = (char*)malloc(sizeof(char)*(size_file_n + 1));
    c++;
	strcpy(rest,c);
    rest[strlen(rest) - 1] = '\0';
	fprintf(fp, "%s", rest);
    
    // Checks if the size of the file is correct
    if(size_file_n == strlen(rest)) {
	printf("Retrieve Finished.\n");
        fclose(fp);
        return;
    }
    else {
        fclose(fp);
        remove(file_name);
        exit_user(CODE_SIZE_02);
    }
}

void upload_content(char* file_name) {
    char cmd[COMMAND_SIZE + FNAME_SIZE];
    char msg[MSG_SIZE];
    char upload_file[COMMAND_SIZE + FNAME_SIZE + 1024];
    char msg_return[1024];
    char* file_data;
    char c;
    int size_file, i;
    char* size_file_c = (char*)malloc(sizeof(char) * COMMAND_SIZE);
    int auxncmd, n_write;
    printf("Starting the upload.\n");
    
    // Initializing TCP
    
    fdTCP = socket(AF_INET,SOCK_STREAM,0);
    if(fdTCP == -1) { exit_user(CODE_TCP_01); }
    
    hostptrTCP = gethostbyname(HOST_TEST);
    memset((void*)&serveraddrTCP,(int)'\0', sizeof(serveraddrTCP));
    serveraddrTCP.sin_family = AF_INET;
    serveraddrTCP.sin_addr.s_addr = ((struct in_addr *)(hostptrTCP->h_addr_list[0]))->s_addr;
    serveraddrTCP.sin_port = htons((u_short)HOST_PORT);
    
    connect(fdTCP,(struct sockaddr*)&serveraddrTCP, sizeof(serveraddrTCP));
    
    // Writes the request for 'upload' to the CS, namely UPR.
    strcpy(cmd,"UPR ");
    strcat(cmd, file_name);
    strcat(cmd, "\n");
    auxncmd = 4 + strlen(file_name) + 2;
    while(auxncmd > 0) {
        if((n_write = write(fdTCP,cmd,strlen(cmd))) == -1) exit(1);
        auxncmd -= n_write;
    }
    
    // Reads the answer and chooses what to do.
    read(fdTCP, msg, sizeof(msg));

    if(!strncmp("AWR new", msg, 7)) { }
    
    else if (!strncmp("AWR dup", msg, 7)) {
        exit_user(CODE_UPD_01);
        return;
    }
    
    else if (!strncmp("ERR", msg, 3)) {
        exit_user(CODE_UPD_02);
        return;
    }
    
    else {
        exit_user(CODE_UPD_03);
        return;
    }
    
    fp = fopen(file_name,"r");
    
    if(fp == NULL) { exit(1); }
    
    if(!fp) {
        exit_user(CODE_FILE_01);
    }
    fseek(fp, 0, SEEK_END);
    size_file = ftell(fp);
    size_file--;
    size_file_c = itoa_n(size_file, size_file_c, 10);
    fseek(fp, 0, SEEK_SET);
    file_data = (char*)malloc(sizeof(char)*(size_file));
	i = 0;	
	while((c = fgetc(fp)) != EOF) {
		if(c != '\n') {
			file_data[i] = c;
			i++;
		}
    }
    strcpy(upload_file,"UPC ");
    strcat(upload_file, size_file_c);
    strcat(upload_file, " ");
    strcat(upload_file, file_data);
    strcat(upload_file, "\n");
    auxncmd = strlen(upload_file);

    fdTCP = socket(AF_INET,SOCK_STREAM,0);
    if(fdTCP == -1) { exit_user(CODE_TCP_01); }
    
    hostptrTCP = gethostbyname(HOST_TEST);
    memset((void*)&serveraddrTCP,(int)'\0', sizeof(serveraddrTCP));
    serveraddrTCP.sin_family = AF_INET;
    serveraddrTCP.sin_addr.s_addr = ((struct in_addr *)(hostptrTCP->h_addr_list[0]))->s_addr;
    serveraddrTCP.sin_port = htons((u_short)HOST_PORT);
    
    connect(fdTCP,(struct sockaddr*)&serveraddrTCP, sizeof(serveraddrTCP));

    while(auxncmd > 0){
        if((n_write = write(fdTCP,upload_file,strlen(upload_file))) == -1) {
            exit(1);
        }
        auxncmd -= n_write;
    }

    // Reads the answer.
    read(fdTCP,msg_return,sizeof(msg_return));
	close(fdTCP);
    
    // Checks the return of the CS
    if(!strncmp("AWC ok", msg_return, 6)) {
        printf("Upload finished.\n");
        return;
    }
    
    else if (!strncmp("AWC nok", msg_return, 7)) {
        printf("Couldn't upload the file.\n");
        exit_user(CODE_UPD_04);
        return;
    }
    
    else if (!strncmp("ERR", msg_return, 3)) {
        printf("Couldn't upload the file.\n");
        exit_user(CODE_UPD_05);
        return;
    }
    
    else {
        printf("Couldn't upload the file.\n");
        exit_user(CODE_UPD_03);
        return;
    }
}

char* itoa_n(int num, char* str, int base)
{
    int i = 0;
    int isNegative = OFF;
    
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = ON;
        num = -num;
    }
    
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
    
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
    
    str[i] = '\0'; // Append string terminator
    
    // Reverse the string
    reverse_n(str, i);
    
    return str;
}

void reverse_n(char str[], int length)
{
    int start = 0;
    int end = length -1;
    char c;
    while (start < end)
    {
        c = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = c;
        start++;
        end--;
    }
}

int myAtoi(char *str)
{
    int res = 0; // Initialize result
    int i = 0;
    
    // Iterate through all characters of input string and update result
    for (i = 0; str[i] != '\0' && str[i] != ' '; ++i)
        res = res*10 + str[i] - '0';
    
    // return result.
    return res;
}
