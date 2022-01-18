/*
    UDP-Client
*/
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
 #define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which data will be sent 
 
void die(char *sockfd)
{
	//For any error message 
    perror(sockfd);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in si_other;
    int sockfd, i, slen=sizeof(si_other);
    
    char buf[BUFLEN];
    char message[BUFLEN];
 
    if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)//Creating  Socket 
    {
        die("socket");
    }
    puts("Socket created");
 
    memset((char *) &si_other, 0, sizeof(si_other));
	//Assigning IP, PORT 
    si_other.sin_family = AF_INET;//Server Domain
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 //Communication between Client and Server
    while(1)
    {
        printf("Enter the expression in the num1 operand num2 form  ");
        gets(message);
         
        //Sending the Data to the Server
        if (sendto(sockfd, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         puts("Data Sent to the server");
		 memset(buf,'\0', BUFLEN);//Clearing the buffer by filling null as it may have previously rec data
        //trying  to receive some data
        if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
        puts("rec fail");
            die("recvfrom()");
            break;
        }
         
        
    }
 //Socket Closed 
    close(sockfd);
    return 0;
}
