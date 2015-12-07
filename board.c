#include <stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include "board.h"
#include <string.h>
//funkcja tworzy podstawowe dane o rozgrywce
struct board *init_board(int forPlayer)
{
	struct board *b;
	b=(struct board*)malloc(sizeof(struct board));
	memset(b,0,sizeof(b->table));
	int i;
	for(i=0;i<3;i++) 
	{
		if(forPlayer==1||forPlayer==0)b->table[BOARDSIZE/2-2+i][0]=1;
		if(forPlayer==2||forPlayer==0)b->table[0][BOARDSIZE-3+i]=2;
		if(forPlayer==3||forPlayer==0)b->table[BOARDSIZE-1][BOARDSIZE-3+i]=3;
	}
	return b;
}

// funkcja wypisuje plansze na ekran
void print_board(struct board *b){
	int x,y;
	for(y=0;y<BOARDSIZE+2;y++)
	{
		for(x=0;x<BOARDSIZE+2;x++)
		{
			if(x==0||y==0||x==BOARDSIZE+1||y==BOARDSIZE+1)
				printf("#");
			else
			{
				printf("%d",b->table[x-1][y-1]);
			}
		}
		printf("\n");
	}
}
//funkcja przygotowuje plansze do wyslania przez siec poprzez wrzucenie jej do napisu
void boardToReasponse(struct board *b,char *response,int hit)
{
	sprintf(response,"newboard %d",hit);  //pierwsza cyfra to informacja o trafieniu
	int i,j;
	for(i=0;i<BOARDSIZE;i++)
		for(j=0;j<BOARDSIZE;j++)
		{
			sprintf(response,"%s %d",response,b->table[j][i]); //w petli doklejamy na koniec kolejna cyfre opisujaca plansze
		}
}

//funkcja odczytuje zapis tablicy z napisu przekazanego poprzez siec
int responseToBoard(struct board *b,char *response)
{
	int i,j,retval;
	response+=9;
	sscanf(response,"%d",&retval); //odczytujemy pierwsza cyfre czyli informacje o trafieniu
			response+=2;
	for(i=0;i<BOARDSIZE;i++)
		for(j=0;j<BOARDSIZE;j++)
		{
			sscanf(response,"%d",&b->table[j][i]);//odczytujemy pierwsza cyfre z napisu
			response+=2; //odcinamy pierwsza cyfre z napisu dzieki temu w kolejnych przejsciach petli mamy kolejne cyfry
			
			
		}
	return retval;
}

//sprawdzenie poprawnosci ruchu
// 0 - ruch nie poprawny
// 1 - ruch poprawny
// 2 - strzal poprawny
// 3 - ruch na pole zajete przez inna lodz
int moveProper(struct board *b,int fromX,int fromY,int toX, int toY,int movetype,int playerNr)
{
	if(toX>=BOARDSIZE)return 0;	
	if(toY>=BOARDSIZE)return 0;
	if(fromX>=BOARDSIZE)return 0;
	if(fromY>=BOARDSIZE)return 0;
	if(toX<0)return 0;
	if(toY<0)return 0;
	if(fromX<0)return 0;
	if(fromY<0)return 0;
	if(b->table[fromX][fromY]!=playerNr) return 0;
	if(movetype==2)
	{
		if(fromX>toX+3)return 0;
		if(fromY>toY+3)return 0;
		if(fromX<toX-3)return 0;
		if(fromY<toY-3)return 0;
		return 2;
	}
	else
	{
	   if(fromX>toX+1)return 0;
	   if(fromY>toY+1)return 0;
	   if(fromX<toX-1)return 0;
	   if(fromY<toY-1)return 0;
		
	}
	if(movetype==2)
	{
		if(b->table[toX][toY]!=0) return 2;
		else
		return 0;
	}
	if(movetype==1)
	{
		if(b->table[toX][toY]!=0) return 3;
	}
		
	return 1;
}
//wykonanie ruchu przy zalozeniu ze ruch jest poprawny
int move(struct board *b,int fromX,int fromY,int toX, int toY,int movetype,int playerNr)
{
	
	if(moveProper(b,fromX,fromY,toX,toY,movetype,playerNr)==1)
	{
		
		b->table[toX][toY]=b->table[fromX][fromY];
		b->table[fromX][fromY]=0;
		return 1;
	}
	else return 0;
}

