// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 45000
#define MAXLINE 1024

in_port_t puerto;
char ip[17];
in_port_t NumFlujo;
size_t NumSec;

ssize_t  enviarData(void *buf, size_t count);
void recivirData(void *buf, size_t count);
void setServer(in_port_t puerto,void *buf);
void setIni();

// Driver code
int main() {
    setIni();
    enviarData("A234567890B234567890C234567890D2345",3);
    fflush(stdout);

	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	printf("Hello message sent.\n");
	
	return 0;
}//end main

void setIni(){
    NumSec = 777;
    NumFlujo = 5;
}
void setServer(in_port_t p_puerto,void *p_buf){
    puerto = p_puerto;
    strcpy(ip,p_buf);
}

ssize_t  enviarData(void *buf, size_t count){
/*
5B #Secc 
1B #Flujo
V Data - 1000
1B CS 
*/
in_port_t l_NumFlujo = NumFlujo ++ ;
char flujo[2];
char buffer[1008];
int i=0;
sprintf(buffer,"%05d",(int)NumSec);
sprintf(flujo,"%1d",(int)l_NumFlujo);
sprintf(buffer,"%s%s",buffer,flujo);

printf(">>%s<<",buffer);
/*
int t = length(buf) ;
int pi=0;
for(i=1;i<=count;i=i+1000){
    if (pi < t){
        pi = pi +1000;
    }else{ 
        pi = t-pi+1000;
    }


}
*/


for(i=1;i<=count;i=i+10){   //1000 1000 1000 555
    
    // caso  data solo contiene menso de 1000
    if (strlen(buf) < 10){
        printf("<1000:%s\n",(char *)buf);
    }   
    // ultima parte del dato que es menor a 1000
    /*
    else if ( i >1  && (strlen(buf) % 10 > 0) ){
        char *p = buf;
        char buffTmp[1001];
        p+=((i-1)*10); // p apunta al  milesima(i) posicion en buff 
        strncpy(buffTmp,p,strlen(buf) % 10);
        printf("ultima parte < a 1000:%s\n",(char *)buffTmp);
    }  
    */
    // partes de  1000
    else {
        char *p = buf;
        char buffTmp[1001];
        p+=((i-1)*10); // p apunta al  milesima(i) posicion en buff 
        strncpy(buffTmp,p,10);
        printf("partes de 1000:%s\n",buffTmp);
    }
    

}

return 0;
}
void recivirData(void *buf, size_t count){

}
