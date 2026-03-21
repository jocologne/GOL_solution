#include "life.h"

int main(int argc, char **argv)
{
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int ite = atoi(argv[3]);
	if (w <= 0 || h <= 0 || ite < 0)
		return(argc);
	game_of_life(w, h, ite);
	return(0);
}