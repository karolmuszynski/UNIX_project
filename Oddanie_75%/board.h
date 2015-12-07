#define BOARDSIZE 12
#ifndef BOARD_H
#define BOARD_H
struct board{
	
	int table[ BOARDSIZE][ BOARDSIZE];
		
	};

struct board *init_board();
void print_board(struct board *b);
int move(struct board *b,int fromX,int fromY,int toX, int toY,int movetype,int playerNr);
int moveProper(struct board *b,int fromX,int fromY,int toX, int toY,int movetype,int playerNr);
void boardToReasponse(struct board *b,char *response,int hit);
int responseToBoard(struct board *b,char *response);
#endif
