#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

int main()
{
	srand(time(0));
	int i, j;
	char cmove;
	int candyi  = rand()%16;
	int candyj  = rand()%32;
	int headi   = 7;
	int headj   = 5;
	int dir     = 0;
	int score   = 0;
	int length  = 5;
	int sizing  = 0;
	WINDOW* win = initscr();
	halfdelay(1);
	curs_set(0);
	noecho();

	int f[16][32];

	memset(f, 0, 16*32*sizeof(int));
	f[7][1] = 1;
	f[7][2] = 2;
	f[7][3] = 3;
	f[7][4] = 4;
	f[7][5] = 5;

	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
	}


	attron(COLOR_PAIR(1));
	move(0, 0);
	printw("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw(" xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("x                                                               x\n");
	printw("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw(" xx Score :        xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");



	while (1)
	{
		attron(COLOR_PAIR(3));
		for (i = 0; i < 16; i++)
		{
			move(3 + i, 1);
			for (j = 0; j < 32; j++)
			{
				if (!f[i][j])
				{
					printw(" ");
				}
				else
				{
					printw("o");
				}
				if (j != 31)
				{
					printw(" ");
				}
			}
		}

		attron(COLOR_PAIR(2));
		for (i = 0; i < 16; i++)
		move(20, 12);
		printw("%d", score);
		mvaddch(3 + candyi, 1 + candyj*2, '+');
		refresh();

		switch (dir)
		{
			case 0:
				headj++;
				break;
			case 1:
				headi--;
				break;
			case 2:
				headj--;
				break;
			case 3:
				headi++;
				break;
		}

		if (f[headi][headj] || headi < 0 || headi > 15 || headj < 0 || headj > 31)
		{
			break;
		}

		if (headi == candyi && headj == candyj)
		{
			sizing = 1;
			length++;
			score++;
			while (f[candyi][candyj])
			{
				candyi = rand()%16;
				candyj = rand()%32;
			}
		}

		for (i = 0; i < 16; i++)
		{
			for (j = 0; j < 32; j++)
			{
				if (f[i][j])
				{
					f[i][j]--;
				}
			}
		}

		f[headi][headj] = length;

		/*
		   while (f[tmpi][tmpj] != 1)
		   {
		   f[tmpi][tmpj]--;
		   if (tmpi != 0 && f[tmpi - 1][tmpj] == f[tmpi][tmpj])
		   {
		   tmpi--;
		   }
		   else if (tmpi != 15 && f[tmpi + 1][tmpj] == f[tmpi][tmpj])
		   {
		   tmpi++;
		   }
		   else if (tmpj != 0 && f[tmpi][tmpj - 1] == f[tmpi][tmpj])
		   {
		   tmpj--;
		   }
		   else if (tmpj != 31 && f[tmpi][tmpj + 1] == f[tmpi][tmpj])
		   {
		   tmpj++;
		   }
		   else
		   {
		   printw("PENISEPNESIEPNEISNPENISPENIS\n");
		   refresh();
		   }
		   }
		   f[tmpi][tmpj]--;
		   */

		cmove = getch();

		switch (cmove)
		{
			case 'l':
				if (dir != 2)
				{
					dir = 0;
				}
				break;
			case 'i':
				if (dir != 3)
				{
					dir = 1;
				}
				break;
			case 'j':
				if (dir != 0)
				{
					dir = 2;
				}
				break;
			case 'k':
				if (dir != 1)
				{
					dir = 3;
				}
				break;
		}
	}


	clear();
	refresh();
	endwin();
	refresh();
}
