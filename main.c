#include "life.h"

int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int ite = atoi(argv[3]);
	if (w <= 0 || h <= 0 || ite < 0)
		return 2;
	game_of_life(w, h, ite);
	return 0;
}