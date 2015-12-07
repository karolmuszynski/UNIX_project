#include <stdio.h>
#include "game.h"
#ifndef GAME_SERVER_H
#define GAME_SERVER_H
void parseRequest(struct game **g,int *currentGame, char* request,char *response);
#endif
