#include "game_client.h"

//funkcja analizuje odpowiedz serwera wywoluje odpowiednia funkcje by gracz mogl zareagowac a nastepnie generuje odpowiedni request
void parseResponse(struct game *g,char* response,char *request)
{
		char command[16];
		sscanf(response,"%s",command); //wczytujemy rozkaz
		
		if(strcmp(command,"newboard")==0) //od serwera otrzymalismy plansze
		{			
			int ret=responseToBoard(g->players[g->playerNumber-1],response); 
			if(ret!=0)
				if(ret>1)
					printf("TRAFIONY ZATOPIONY!!!\n");
				else
					printf("PUDLO!!!\n");
			
			print_board(g->players[g->playerNumber-1]); //wypisujemy nowa plansze
			int fx,fy,tx,ty,mt;
			printf("Enter number (x,y)->(tx,ty) mt");
			scanf("%d %d %d %d %d",&fx,&fy,&tx,&ty,&mt); //prosimy gracza o nowy ruch
			moveInGameRequest(g,fx,fy,tx,ty,mt,g->playerNumber,request); //tworzymy odpowiedni request do serwera
		}
		if(strcmp(command,"newgame")==0) //serwer nam mowi ze zaczela sie nowa gra
		{
			printf("rozpoczeto nowa rozgrywke\n");
			
			sscanf(response,"%s %d",command,&g->playerNumber);
			sprintf(request,"loadboard %d",g->playerNumber);
		}
		if(strcmp(command,"waiting")==0) //serwer kaze nam czekac na nowa gre
		{
			printf("oczekiwanie na innych graczy\n");
			fflush(stdout);
			sscanf(response,"%s %d",command,&g->playerNumber);
			sprintf(request,"waiting %d",g->playerNumber);
			sleep(1);
		}
		if(strcmp(command,"creategame")==0) //powinnismy poprosic o stworzenie nowej gry
		{
			
			sprintf(request,"newgame");
		}
		if(strcmp(command,"status")==0) //otrzymujemy informacje o stanie gry
		{
			int status;
			sscanf(response,"%s %d",command,&status);
			if(status==1)
				printf("\n\n\nprzegrales koniec gry\n\n");
			if(status==2)
				printf("\n\n\nZwyciestwo!!!!\n\n");
			sprintf(request,"newgame");
		}
		
		
	}

