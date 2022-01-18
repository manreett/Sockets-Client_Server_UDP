/*
    UDP-Server
*/
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port to listen for incoming data 
 
void die(char *sockfd)
{
	
	perror(sockfd);
    exit(1);
}
 
int main(void)
{
    
    struct sockaddr_in si_me, si_other;
    float op1;
    float op2;
    char operator; 
    int sockfd, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    int result;
	char res[BUFLEN];
     
    //create a UDP socket
    if ((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)//UDP Socket Creation 
    {
        die("socket");
    }
    puts("Socket Created");
     
    // this zero out the structure that 
    memset((char *) &si_me, 0, sizeof(si_me));
     //Assiging IP, PORT
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //Binding the socket with the server address
    if( bind(sockfd , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
    puts("Binding Done");
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
         
        //Try to receive some data 
        if ((recv_len = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
           puts("Recv failed");
            die("recvfrom()");
        }
        
        
        printf(" Received Data: %s\n" , buf);
		//Code for Calculator Functioning 
	if(sscanf(buf, "%f %1[+-/*] %f", &op1, &operator, &op2) == 3)
    {
        printf("Operand 1: %.2f\n", op1);
        printf("Operand 2: %.2f\n", op2);
        printf("Operator: %c\n", operator);
	switch ( operator )
  {
     case '+' :
      result = op1 + op2;
   printf("Result is: %.2f + %.2f = %d\n",op1, op2, result);
     break;
 
     case '-' :
       result = op1 - op2;
   printf("Result is: %.2f - %.2f = %d\n",op1, op2, result);
     break;
 
     case '*' :
        result = op1 * op2;
   printf("Result is: %.2f * %.2f = %d\n",op1, op2, result);
     break;
 
     case '/' :
       result = op1 / op2;
   printf("Result is: %.2f / %.2f = %d\n",op1, op2, result);
     break;
	  default :
       printf ("Invalid Selection \n");
  	}
 	}
	sprintf(res, "%i", result);

        //Replying the client with same data 
        if (sendto(sockfd, res, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        
        
    }
 
    close(sockfd);
    return 0;
}
