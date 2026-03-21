#include "life.h"

void free_board(char **board, int h)
{
	int line = 0;
	while (line < h)
	{
		free(board[line]);
		line++;
	}
	free(board);
}

char **create_board(int w, int h)
{
	char **empty_board;
	int index = 0;
	int array = 0;
	empty_board = (char **)calloc(h + 1, sizeof(char *));
	while (array < h)
	{
		empty_board[array] = (char *)calloc(w + 1, sizeof(char));
		index = 0;
		while (index < w)
		{
			empty_board[array][index] = '.';
			index++;
		}
		empty_board[array][index] = '\0';
		array++;
	}
	return empty_board;
}

char **populate_board(int w, int h)
{
	char buf;
	int index = 0;
	int line = 0;
	bool draw = false;
	char **board = create_board(w, h);
	while (read(0, &buf, 1) > 0)
	{
		if (buf == 'x')
			draw = !draw;
		else if (buf == 'w' && (line - 1 >= 0))
			line--;
		else if (buf == 'a' && (index - 1 >= 0))
			index--;
		else if (buf == 's' && (line + 1 < h))
			line++;
		else if (buf == 'd' && (index +1 < w))
			index++;
		if (draw)
			board[line][index] = '0';
	}
	return board;
}

void print_board(char **board, int w, int h)
{
	int index = 0;
	int line = 0;
	while (line < h)
	{
		index = 0;
		while(index < w)
		{
			putchar(board[line][index]);
			index++;
		}
		putchar('\n');
		line++;
	}
}

int count_cells(char **board, int w, int h, int col, int lin)
{
	int count = 0;
	for (int dl = -1; dl <= 1; dl++)
	{
		for (int dc = -1; dc <= 1; dc++)
		{
			if (dl == 0 && dc == 0)
				continue;
			int nlin = lin + dl;
			int ncol = col + dc;
			if (nlin < 0 || nlin >= h)
				continue;
			if (ncol < 0 || ncol >= w)
				continue;
			if (board[nlin][ncol] != '0')
				continue;
			count++;
		}
	}
	return count;
}

char **update_board(char **board, int w, int h)
{
	char **new_board = create_board(w, h);
	int index;
	int line = 0;

	while (line < h)
	{
		index = 0;
		while (index < w)
		{
			int cell_counter = count_cells(board, w, h, index, line);

			int alive = (board[line][index] == '0');
			int survive = (cell_counter == 2 || cell_counter == 3);
			int born = (cell_counter == 3);

			if (alive && survive)
				new_board[line][index] = '0';
			else if (!alive && born)
				new_board[line][index] = '0';

			index++;
		}
		line++;
	}
	free_board(board, h);
	return (new_board);
}

void game_of_life(int w, int h, int ite)
{
	char **board = populate_board(w, h);
	print_board(board, w, h);
	printf("\n");
	while (ite--)
	{
		board = update_board(board, w, h);
		print_board(board, w, h);
		printf("\n");
	}
	free_board(board, h);
}