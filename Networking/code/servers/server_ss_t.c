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
#define CODE_UDP_01 "FD ERROR: UDP'S SOCKET FAILED"
#define CODE_TCP_01 "FD ERROR: TCP'S SOCKET FAILED"
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


void exit_user(char* message);
int myAtoi(char *str);
char* itoa_n(int num, char* str, int base);
void reverse_n(char str[], int length);

int main() {
	int fd, fd_ret, newfd, size_file, size_file_up, clientlen, posbuffer, i, j, index, size_msg, aux_write;
	char buffer[1024];
	char* msg;
    char file_name[20];
    char size_file_buffer[2];
	char *data, *filename, *size_file_c;
	char* c;
	char* c_ret;
	char* auxsize;
	char* auxname;
	char* filename_ret;
	char* data_ret;
    char* pointer;
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
		
		if((newfd=accept(fd,(struct sockaddr*)&clientaddr, &clientlen) == -1)) exit(1);
		
		read(newfd, buffer, sizeof(buffer));

        // The SS only acts in two situations
        // Either it's a Request or an Upload
        // In this situation, it's a Request
        
		if(!strncmp(buffer, "REQ ", 4)) {
			// Take the name out of the request
            pointer = buffer;
            pointer += 4;
            
            for(j = 0; j < 20; j++, pointer++){
                if (*(pointer + 1) == '\n') {
                    break;
                }
                file_name[j] = *(pointer);
            }
            
            // Checks if the protocol is respected, according to the size
            // of the file's name
            // If not, sends a error to the Client
            if ((*(pointer + 1) != '\n') && (j == 19)) {
                msg = (char*)malloc(sizeof(char)*5);
                strcpy(msg,"ERR");
                strcat(msg, "\n");
                size_msg = strlen(msg);
                while(size_msg > 0) {
                    if((aux_write = write(newfd, msg, sizeof(msg))) == -1) exit(1);
                    size_msg -= aux_write;
                }
                break;
            }
            
            // Tries to open the file. Then, checks if it exists.
            // If not, sends a error to the Client.
            if((fp = fopen(file_name,"r")) == -1) { exit(1); }
            if(!fp) {
                msg = (char*)malloc(sizeof(char)*9);
                strcpy(msg,"REP nok");
                strcat(msg, "\n");
                size_msg = strlen(msg);
                while(size_msg > 0) {
                    if((aux_write = write(newfd, msg, sizeof(msg))) == -1) exit(1);
                    size_msg -= aux_write;
                }
                break;
            }
            
            // The file's name is ok.
            // Let's read it to a buffer and send it to the Client
            
            // Firstly, let's get the size of the file
            fseek(fp, 0, SEEK_END);
            size_file = ftell(fp);
            size_file_c = itoa_n(size_file, size_file_c, 10);
            
            // Secondly, we reserve memory for the whole return message
            msg = (char*)malloc(sizeof(char)*size_file + 9);
            strcpy(msg,"REP ok ");
            fseek(fp, 0, SEEK_SET);
            index = 7;
            
            // Thirdly, we read the file and extract the information
            while((*(c) = fgetc(fp)) != EOF) {
                msg[index] = *(c);
                index++;
            }
            strcat(msg, "\n");
            size_msg = strlen(msg);
            
            // Lastly, we send it to the client
            while(size_msg > 0) {
                if((aux_write = write(newfd, msg, sizeof(msg))) == -1) exit(1);
                size_msg -= aux_write;
            }
        }
		
        // In this situation, it's an Upload
		else if(!strncmp(buffer, "UPS ", 4)) {
            
            // Take the name out of the request
            pointer = buffer;
            pointer += 4;
            
            for(j = 0; j < 20; j++, pointer++){
                if (*(pointer + 1) == ' ') {
                    break;
                }
                file_name[i] = *(pointer);
            }
            
            if ((*(pointer + 1) != ' ') && (j == 19)) {
                msg = (char*)malloc(sizeof(char)*5);
                strcpy(msg,"ERR");
                strcat(msg, "\n");
                size_msg = strlen(msg);
                while(size_msg > 0) {
                    if((aux_write = write(newfd, msg, sizeof(msg))) == -1) exit(1);
                    size_msg -= aux_write;
                }
                break;
            }
            
            // Reads the size of the file
            for(i = 0; *(pointer) != ' '; i++, pointer++){
                size_file_buffer[i] = *(pointer);
            }
            j = myAtoi(size_file_buffer);
            
            // Opens the file
            if((fp = fopen(file_name,"w")) == -1) { exit(1); }
            if(!fp) {
                exit_user(CODE_FILE_01);
            }
            
            // Writes on the new file the bytes
            for(pointer++; j != 0; j--, pointer++) {
                if(*(pointer) == '\n') {
                    break;
                }
                fprintf(fp, "%c", *(pointer));
            }
            
            // Cheks if the numer of bites written is equal to the size specified before
            if(j != 0) {
                msg = (char*)malloc(sizeof(char)*8);
                strcpy(msg,"AWS nok");
                strcat(msg, "\n");
                size_msg = strlen(msg);
                while(size_msg > 0) {
                    if((aux_write = write(newfd, msg, sizeof(msg))) == -1) exit(1);
                    size_msg -= aux_write;
                }
                remove(file_name);
                break;
            }
            
            msg = (char*)malloc(sizeof(char)*8);
            strcpy(msg,"AWS ok");
            strcat(msg, "\n");
            size_msg = strlen(msg);
            while(size_msg > 0) {
                if((aux_write = write(newfd, msg, sizeof(msg))) == -1) exit(1);
                size_msg -= aux_write;
            }
            
	}
	close(fd); 
	close(newfd);
	return 0;
    }
}

int myAtoi(char *str) {
    int res = 0; // Initialize result
    int i = 0;
    
    // Iterate through all characters of input string and update result
    for (i = 0; str[i] != '\0' && str[i] != ' '; ++i)
        res = res*10 + str[i] - '0';
    
    // return result.
    return res;
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

void exit_user(char* message) {
    // Depending on the message, we should terminate the program in a different way, reporting the error to the user
    printf("%s\n", message);
}