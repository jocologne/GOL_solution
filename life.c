
#include "life.h"

bool is_alive (char c)
{
	return(c == LIVE);
}

bool survive (int count)
{
	return (count == 2 || count ==3);
}

bool born(int count)
{
	return(count == 3);
}

void free_board(t_board board)
{
	int line = 0;
	if (!board.grid)
		return;
	while (line < board.h)
	{
		free(board.grid[line]);
		line++;
	}
	free(board.grid);
}

void print_board(t_board board)
{
	int index = 0;
	int line = 0;
	while(line < board.h)
	{
		index = 0;
		while (index < board.w)
		{
			char c = board.grid[line][index];
			putchar(c);
			index++;
		}
		putchar('\n');
		line++;
	}
}

t_board create_board(int w, int h)
{
	int index = 0;
	int line = 0;
	t_board board;
	board.h = h;
	board.w = w;
	char **empty_board;
	empty_board = (char **)calloc(h, sizeof(char*));
	while(line < h)
	{
		empty_board[line] = (char *)calloc(w, sizeof(char));
		index = 0;
		while (index < w)
		{
			empty_board[line][index] = DEAD;
			index++;
		}
		line++;
	}
	board.grid = empty_board;
	return board;
}

int count_cells(t_board board, int x, int y)
{
    int count = 0;
    for (int dl = -1; dl <= 1; dl++)
    {
        for (int di = -1; di <= 1; di++)
        {
            int pox = x + di;
            int poy = y + dl;
            if (pox < 0 || pox >= board.w)
                continue;
            if (poy < 0 || poy >= board.h)
                continue;
            if (pox == x && poy == y)
                continue;
            if (board.grid[poy][pox] == LIVE)
                count++;
        }
    }
    return count;
}

t_board update_board(t_board board)
{
	int index = 0;
	int line = 0;
	t_board new_board = create_board(board.w, board.h);
	int count = 0;
	while (line < new_board.h)
	{
		index = 0;
		while (index < new_board.w)
		{
			count = count_cells(board, index, line);
			if (is_alive(board.grid[line][index]) && survive(count))
				new_board.grid[line][index] = LIVE;
			else
				if (born(count))
					new_board.grid[line][index] = LIVE;
			index++;
		}
		line++;
	}
	free_board(board);
	return new_board;	
}

t_board populate_board(int w, int h)
{
	char buf;
	int index = 0;
	int line = 0;
	bool draw = false;
	t_board board = create_board(w, h);
	while (read(0, &buf, 1) > 0)
	{
		if (buf == 'x')
			draw = !draw;
		else if (buf == 'w' && line > 0)
			line--;
		else if (buf == 's' && line < h -1)
			line++;
		else if (buf == 'a' && index > 0)
			index--;
		else if (buf == 'd' && index < w -1)
			index++;
		else
			continue;
		if (draw)
			board.grid[line][index] = LIVE;
	}
	return board;
}

void game_of_life(int w, int h, int ite)
{
	t_board board = populate_board(w, h);
	while (ite)
	{
		board = update_board(board);
		print_board(board);
		putchar('\n');
		ite--;
	}
	print_board(board);
	free_board(board);
}