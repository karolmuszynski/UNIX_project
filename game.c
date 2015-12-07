#include "game.h"
#include <stdlib.h>
#include <stdio.h>

//inicjacja gry
struct game* init_game()
{
	int i;
	struct game *g=(struct game*)malloc(sizeof(struct game));
	g->b=init_board(0);
	for(i=0;i<3;i++)
		g->players[i]=init_board(i+1);
	g->numberOfPlayers=0;
	
}


//wykonanie ruchu w odpowiedniej grze
int moveInGame(struct game *g,int fromX,int fromY,int toX, int toY,int movetype,int playerNr)
{
	int i;
	printf("moveingame\n");
	int ocenaRuchu=moveProper(g->b,fromX,fromY,toX,toY,movetype,playerNr);
	if(ocenaRuchu!=0)
	{
		if(ocenaRuchu==1)// ruszamy sie
		{
			printf("moveingame2\n");
			move(g->b,fromX,fromY,toX,toY,movetype,playerNr);
			for(i=0;i<3;i++)
				move(g->players[i],fromX,fromY,toX,toY,movetype,playerNr);
		}
		else if(ocenaRuchu==2) //strzelamy
		{
			int retval;
			retval=g->b->table[toX][toY];
			g->b->table[toX][toY]=0;
			for(i=0;i<3;i++)
			{	
				g->players[i]->table[toX][toY]=0;
				g->players[i]->table[fromX][fromY]=g->b->table[fromX][fromY];
			}
			return retval+1; //zwracamy informacje o trafieniu
		}
		else if(ocenaRuchu==3) //wpadamy na inna lodz
		{
			g->players[g->b->table[toX][toY]-1]->table[fromX][fromY]=g->b->table[fromX][fromY];
			g->players[g->b->table[fromX][fromY]-1]->table[toX][toY]=g->b->table[toX][toY];
		}
	}
	return 0;
}

//zbudowanie requestu proszacego o wykonanie ruchu
void moveInGameRequest(struct game *g,int fromX,int fromY,int toX, int toY,int movetype,int playerNr,char * request)
{
	sprintf(request,"move %d %d %d %d %d %d",fromX,fromY,toX,toY,movetype,playerNr);
}


//sprawdzenie czy gra nie zostala zakonczona wygrana/przegrana etc.
int getStatus(struct game *g,int nrGracza)
{
	int i,j;
	int lodzie[3],iluzlodziami=0;;
	lodzie[0]=lodzie[1]=lodzie[2]=0;
	for(i=0;i<BOARDSIZE;i++)
		for(j=0;j<BOARDSIZE;j++)
			if(g->b->table[i][j]!=0)
			{
				lodzie[g->b->table[i][j]-1]++; //zliczamy liczbe lodzi kazdego gracza
			}
	if(lodzie[nrGracza-1]==0) //jak nasz gracz nie ma lodzi to przegral
		return 1;
	for(i=0;i<3;i++)if(lodzie[i]!=0)iluzlodziami++;
	
	if(iluzlodziami==1)return 2; //jezeli nasz gracz jest ostatnim posiadaczem lodzi to wygral
		else return 0; //gra trwa nadal
}
