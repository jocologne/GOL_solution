#ifndef LIFE_H
#define LIFE_H

#define DEAD '.'
#define LIVE '0'

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct s_board
{
	int w;
	int h;
	char **grid;
} t_board;


void game_of_life(int w, int h, int ite);

#endif