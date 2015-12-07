#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include "game_client.h"
 
int main(int argc , char *argv[])
{
	if(argc!=2)
		{
			printf("podaj ip servera");
			return 1;
		}
    int sock;
    struct sockaddr_in server;
    struct game *g=init_game();
    char message[1000] , server_reply[2000];
     sprintf(server_reply,"creategame");
    while(1)
    {
        parseResponse(g,server_reply,message);
        
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    
     
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

     

        //Send some data
        if( send(sock , message , strlen(message)+1 , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        close(sock);
        
    }
     
    
    return 0;
}
