#include "game_server.h"

//funkcja przetwarzajaca request klienta wywolujaca odpowiednie funkcje dla odpowiedniej gry oraz generujaca odpowiedz
void parseRequest(struct game **g,int *currentGame,char* request,char *response)
{
	char command[16];
		sscanf(request,"%s",command); //wczytujemy rozkaz
		
		if(strcmp(command,"move")==0)//ruch
		{
			int fx,fy,tx,ty,mt,player;
			sscanf(request,"%s %d %d %d %d %d %d",command,&fx,&fy,&tx,&ty,&mt,&player);
			if(getStatus(g[player/10],player%10)!=0)
			{
				sprintf(response,"status %d",getStatus(g[player/10],player%10));  //jezeli gra sie skonczyla to zwracamy status
			}
			else
			{
				int retval=moveInGame(g[player/10],fx,fy,tx,ty,mt,player%10);
				boardToReasponse(g[player/10]->players[player%10-1],response,retval); //jezeli gra trwa dalej to zwracamy plansze dla aktualnego gracza
			}
		}
		if(strcmp(command,"loadboard")==0) //wczytanie planszy
		{
			int player;
						sscanf(request,"%s %d",command,&player);
			
			boardToReasponse(g[player/10]->players[player%10-1],response,0);
		}
		if(strcmp(command,"newgame")==0)// prosba o podlaczenie do nowej gry
		{

			g[*currentGame]->numberOfPlayers++;
			if(g[*currentGame]->numberOfPlayers==3) //gdy mamy wszystkich graczy gra sie zaczyna
			{
				sprintf(response,"newgame %d",3+10*(*currentGame));
				(*currentGame)++;
				
			}
			else //gdy brakuje graczy kazemy graczowi czekac
			{
				sprintf(response,"waiting %d",g[*currentGame]->numberOfPlayers+10*(*currentGame));
			}
			
		}
		if(strcmp(command,"disconnect")==0) // rozlaczenie w trakcie rozgrywki
		{
			int nrPlayer;
			sscanf(request, "%s %d",command,&nrPlayer);
			sprintf(response,"disconnected");
			clearPlayer(g[nrPlayer/10],nrPlayer%10);
			}
		if(strcmp(command,"waiting")==0)//request pytajacy czy dalej trzeba czekac na gre
		{
						int player;						
						sscanf(request,"%s %d",command,&player);						
						if(g[player/10]->numberOfPlayers==3) //mozna zaczynac
						{
							sprintf(response,"newgame %d",player);
							
						}
						else //trzeba czekac dalej
						{
							printf("waiting %d\n",player);
							sprintf(response,"waiting %d",player);
						}
					}
			
	}
