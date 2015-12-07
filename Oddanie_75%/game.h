#include "board.h"
#ifndef GAME_H
#define GAME_H
struct game
{
	struct board *b //prawdziwa plansza gry
	,*players[3]; //plansze widoczne przez poszczegolnych graczy
	int playerNumber;
	int numberOfPlayers;
	
};

struct game* init_game();
int moveInGame(struct game *b,int fromX,int fromY,int toX, int toY,int movetype,int playerNr);
int getStatus(struct game *g,int nrGracza);
#endif
