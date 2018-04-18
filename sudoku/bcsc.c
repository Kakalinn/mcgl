#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
	int i;
	int j;
} par;

void fischer_yates(int* f, int n);

int main()
{
	srand(time(0));
	int i, j, k, l, m;

	int givensc = 0;
	int givens[9][9];
	int filled[9][9];
	memset(givens, 0, 9*9*sizeof(int));
	memset(filled, 0, 9*9*sizeof(int));

	int solution[9][9] = 
	{
		{1, 2, 3, 4, 5, 6, 7, 8, 9},
		{4, 5, 6, 7, 8, 9, 1, 2, 3},
		{7, 8, 9, 1, 2, 3, 4, 5, 6},
		{2, 3, 4, 5, 6, 7, 8, 9, 1},
		{5, 6, 7, 8, 9, 1, 2, 3, 4},
		{8, 9, 1, 2, 3, 4, 5, 6, 7},
		{3, 4, 5, 6, 7, 8, 9, 1, 2},
		{6, 7, 8, 9, 1, 2, 3, 4, 5},
		{9, 1, 2, 3, 4, 5, 6, 7, 8}
	};

	int perm[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};


	/* Gen sol */
	for (i = 0; i < 1000000; i++)
	{
		int r1 = rand()%5;
		int r2 = rand()%3;
		int r3 = rand()%3;
		int r4 = rand()%3;

		switch (r1)
		{
			case 0:
				for (j = 0; j < 9; j++)
				{
					int tmp = solution[r2*3 + r3][j];
					solution[r2*3 + r3][j] = solution[r2*3 + r4][j];
					solution[r2*3 + r4][j] = tmp;
				}
				break;

			case 1:
				for (j = 0; j < 9; j++)
				{
					int tmp = solution[j][r2*3 + r3];
					solution[j][r2*3 + r3] = solution[j][r2*3 + r4];
					solution[j][r2*3 + r4] = tmp;
				}
				break;
			case 2:
				for (j = 0; j < 9; j++)
				{
					int tmp = solution[j][r2*3 + 0];
					solution[j][r2*3 + 0] = solution[j][r3*3 + 0];
					solution[j][r3*3 + 0] = tmp;

					tmp = solution[j][r2*3 + 1];
					solution[j][r2*3 + 1] = solution[j][r3*3 + 1];
					solution[j][r3*3 + 1] = tmp;

					tmp = solution[j][r2*3 + 2];
					solution[j][r2*3 + 2] = solution[j][r3*3 + 2];
					solution[j][r3*3 + 2] = tmp;
				}
				break;
			case 3:
				for (j = 0; j < 9; j++)
				{
					int tmp = solution[r2*3 + 0][j];
					solution[r2*3 + 0][j] = solution[r3*3 + 0][j];
					solution[r3*3 + 0][j] = tmp;

					tmp = solution[r2*3 + 1][j];
					solution[r2*3 + 1][j] = solution[r3*3 + 1][j];
					solution[r3*3 + 1][j] = tmp;

					tmp = solution[r2*3 + 2][j];
					solution[r2*3 + 2][j] = solution[r3*3 + 2][j];
					solution[r3*3 + 2][j] = tmp;
				}
				break;
			case 4:
				fischer_yates(&(perm[0]), 9);

				for (j = 0; j < 9; j++)
				{
					for (k = 0; k < 9; k++)
					{
						solution[j][k] = perm[solution[j][k] - 1] + 1;
					}
				}
				break;
		}
	}

	/* GIVE NUMBERS */
	for (i = 0; i < 35; i++)
	{
		int r1 = rand()%9;
		int r2 = rand()%9;

		while (givens[r1][r2])
		{
			r1 = rand()%9;
			r2 = rand()%9;
		}

		givens[r1][r2] = 1;
		givensc++;
	}

	/*
	   for (i = 0; i < 9; i++)
	   {
	   for (j = 0; j < 9; j++)
	   {
	   printf("%d ", solution[i][j]);
	   }
	   printf("\n");
	   }
	   */




	/* Play */
	WINDOW* win = initscr();
	//resize_term(13, 25);
	noecho();

	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_BLACK);
		init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(4, COLOR_RED, COLOR_BLACK);
	}

	/*
	   move(0, 0);
	   printw("        ,       ,\n");
	   printw("        |       |\n");
	   printw("        |       |\n");
	   printw("        |       |\n");
	   printw(" -------+-------+-------\n");
	   printw("        |       |\n");
	   printw("        |       |\n");
	   printw("        |       |\n");
	   printw(" -------+-------+-------\n");
	   printw("        |       |\n");
	   printw("        |       |\n");
	   printw("        |       |\n");
	   printw("        '       '");
	   */

	char c;
	int loci = 0;
	int locj = 0;
	while (1)
	{
		move(0, 0);
		attron(COLOR_PAIR(1));
		printw("        ,       ,\n");
		for (i = 0; i < 9; i++)
		{
			printw("  ");
			for (j = 0; j < 9; j++)
			{
				if (givens[i][j])
				{
					attron(COLOR_PAIR(2));
					printw("%d ", solution[i][j]);
				}
				else if (filled[i][j])
				{
					attron(COLOR_PAIR(3));
					printw("%d ", filled[i][j]);
				}
				else
				{
					attron(COLOR_PAIR(4));
					printw(". ");
				}
				attron(COLOR_PAIR(1));
				if (j%3 == 2 && j != 8)
				{
					printw("| ");
				}
			}
			attron(COLOR_PAIR(1));
			printw("\n");
			if (i%3 == 2 && i != 8)
			{
				printw(" -------+-------+-------\n");
			}
		}
		printw("        '       '\n");

		move(1 + loci + loci/3, 2 + 2*locj + locj/3*2);
		refresh();

		while (1)
		{
			c = getch();

			switch (c)
			{
				/* HACK CHEAT SVINDL */
				case '.':
					for (i = 0; i < 9; i++)
					{
						for (j = 0; j < 9; j++)
						{
							givens[i][j] = 1;
						}
					}
					break;




				case 'q':
					break;

				case 'd':
				case 'l':
					locj++;
					if (locj > 8)
					{
						locj = 8;
					}
					break;

				case 'a':
				case 'h':
					locj--;
					if (locj < 0)
					{
						locj = 0;
					}
					break;

				case 's':
				case 'j':
					loci++;
					if (loci > 8)
					{
						loci = 8;
					}
					break;

				case 'w':
				case 'k':
					loci--;
					if (loci < 0)
					{
						loci = 0;
					}
					break;

				case 'c':
					c = getch();

					if (c == 'c')
					{
						for (i = 0; i < 9; i++)
						{
							for (j = 0; j < 9; j++)
							{
								if (filled[i][j])
								{
									if (filled[i][j] == solution[i][j])
									{
										filled[i][j] = 0;
										givens[i][j] = 1;
										givensc++;
									}
									else
									{
										break;
									}
								}
							}
							if (j != 9)
							{
								break;
							}
						}
						if (i != 9)
						{
							c = 'q';
						}
					}

					break;

				case 'X':
					for (i = 0; i < 9; i++)
					{
						for (j = 0; j < 9; j++)
						{
							filled[i][j] = 0;
						}
					}
					break;

				case 'x':
					filled[loci][locj] = 0;
					break;

				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':;
						 int t = c - '0';

						 if (!givens[loci][locj])
						 {
							 filled[loci][locj] = c - '0';
						 }
						 break;
			}
			move(1 + loci + loci/3, 2 + 2*locj + locj/3*2);

			if (c == 'x' || c == 'X' || c == 'c' || (c <= '9' && c >= '0') || c == 'q')
			{
				break;
			}
		}


		if (givensc == 81 || c == 'q')
		{
			break;
		}

	}
	clear();
	refresh();
	endwin();
	refresh();
	return 0;
}


void fischer_yates(int* f, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		int m = rand()%(n - i);

		int tmp = f[m];
		f[m] = f[n - i - 1];
		f[n - i - 1] = tmp;
	}
}



/*
   ,       ,
   x x x | x x x | x x x
   x x x | x x x | x x x
   x x x | x x x | x x x
   -------+-------+-------
   x x x | x x x | x x x
   x x x | x x x | x x x
   x x x | x x x | x x x
   -------+-------+-------
   x x x | x x x | x x x
   x x x | x x x | x x x
   x x x | x x x | x x x
   '       '
   */
