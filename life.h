#ifndef LIFE_H
#define LIFE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define LIVE '0'
#define DEAD ' '

void game_of_life(int w, int h, int ite);

#endif