#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include "game_server.h"
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    int currentGame=0;
    struct game *g[100];
    int i;
    for (i=0;i<100;i++)
		g[i]=init_game();
    struct sockaddr_in server , client;
    char client_message[2000];
     char response[2560];
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
 while(1)
 {    
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
		puts("client message");
        puts(client_message);
        printf("\n");
        //Send the message back to client
        parseRequest(g,&currentGame,client_message,response);
        write(client_sock , response , strlen(response)+1);
    }
 }
    
     
    return 0;
}
