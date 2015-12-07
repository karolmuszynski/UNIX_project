#include "board.h" 
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	struct game *g=init_game();
	int nrPlayer=1;
	while(1)
	{
		printf("numer gracza%d\n",nrPlayer);
		print_board(g->b);
		print_board(g->players[nrPlayer-1]);
		int fx,fy,tx,ty,mt;
		printf("Enter number (x,y)->(tx,ty) mt");
		scanf("%d %d %d %d %d",&fx,&fy,&tx,&ty,&mt);
		moveInGame(g,fx,fy,tx,ty,mt,nrPlayer);
	//	nrPlayer=nrPlayer%3 +1; 
	}
	free(g);
	return 0;
	}
	
