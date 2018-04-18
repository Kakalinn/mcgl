#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



int black_and_white = 1;


void set_color_as(int i)
{
	if (!black_and_white)
	{
		attron(COLOR_PAIR(i));
	}
}

void bucket_fill_zeros(char* f, char* nums, int ic, int jc, int loci, int locj)
{
	if (f[loci*ic + locj] != -1)
	{
		return;
	}
	if (locj == -1 || locj == jc)
	{
		return;
	}
	if (loci == -1 || loci == ic)
	{
		return;
	}

	f[loci*ic + locj] = nums[(loci + 1)*(ic + 2) + locj + 1];

	if (nums[(loci + 1)*(ic + 2) + locj + 1] != 0)
	{
		return;
	}

	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci - 1, locj - 1);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci - 1, locj);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci - 1, locj + 1);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci, locj - 1);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci, locj + 1);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci + 1, locj + 1);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci + 1, locj);
	bucket_fill_zeros(&(f[0]), &(nums[0]), ic, jc, loci + 1, locj - 1);
}


void fischer_yates(char* f, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		int m = rand()%(n - i);

		char tmp = f[m];
		f[m] = f[n - i - 1];
		f[n - i - 1] = tmp;
	}
}


int main(int argc, char** argv)
{
	srand(time(0));
	int i, j;
	int ic = 8;
	int jc = 8;
	int bc = 10;

	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-d"))
		{
			i++;
			if (!strcmp(argv[i], "easy"))
			{
				ic = 8;
				jc = 8;
				bc = 10;
			}
			else if (!strcmp(argv[i], "medium"))
			{
				ic = 16;
				jc = 16;
				bc = 40;
			}
			else if (!strcmp(argv[i], "hard"))
			{
				ic = 24;
				jc = 24;
				bc = 99;
			}
			else
			{
				printf("Unknown difficulty \"%s\".\n", argv[i]);
				return 0;
			}
		}
		else if(!strcmp(argv[i], "-h"))
		{
			printf("To change difficulty (easy, medium or hard):\n");
			printf("  %s -d <difficulty>\n", argv[0]);
			printf("To use colormode:\n");
			printf("  %s -c\n", argv[0]);

			return 0;
		}

		else if (!strcmp(argv[i], "-c"))
		{
			black_and_white = 0;
		}

	}


	char f[ic][jc];
	char nums[ic + 2][jc + 2];
	char deck[ic*jc];
	int bombc = bc;

	memset(f, -1, ic*jc*sizeof(char));
	memset(nums, 0, (ic + 2)*(jc + 2)*sizeof(char));
	memset(deck, 1, bc*sizeof(char));
	memset(&(deck[bc]), 0, (ic*jc - bc)*sizeof(char));

	fischer_yates(&(deck[0]), ic*jc);

	for (i = 0; i < ic*jc; i++)
	{
		nums[i/ic + 1][i%jc + 1] -= deck[i];
	}

	for (i = 1; i < ic + 1; i++)
	{
		for (j = 1; j < jc + 1; j++)
		{
			if (!nums[i][j])
			{
				if (nums[i - 1][j] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i - 1][j - 1] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i - 1][j + 1] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i][j - 1] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i][j + 1] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i + 1][j - 1] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i + 1][j] == -1)
				{
					nums[i][j]++;
				}
				if (nums[i + 1][j + 1] == -1)
				{
					nums[i][j]++;
				}
			}
		}
	}

	WINDOW* win = initscr();
	noecho();

	if (!black_and_white)
	{
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	}

	move(0, 0);
	set_color_as(1);
	printw("+");
	for (j = 0; j < jc; j++)
	{
		printw("-+");
	}
	printw("\n");
	for (i = 0; i < ic; i++)
	{
		printw("|");
		for (j = 0; j < jc; j++)
		{
			printw(" |");
		}
		printw("\n");
		printw("+");
		for (j = 0; j < jc; j++)
		{
			printw("-+");
		}
		printw("\n");
	}

	int loci = 0;
	int locj = 0;

	while (1)
	{
		for (i = 0; i < ic; i++)
		{
			for (j = 0; j < jc; j++)
			{
				if (f[i][j] == 9)
				{
					set_color_as(3);
					mvaddch(1 + 2*i, 1 + 2*j, 'P');
				}
				else if (f[i][j] != -1)
				{
					set_color_as(2);
					mvaddch(1 + 2*i, 1 + 2*j, f[i][j] + '0');
				}
				else
				{
					mvaddch(1 + 2*i, 1 + 2*j, ' ');
				}
			}
		}

		if (locj < 0)
		{
			locj = jc - 1;
		}
		set_color_as(4);
		mvprintw(1 + ic*2, 1, "Bombs: %d    ", bombc);
		refresh();
		move(1 + loci*2, 1 + locj*2);
		char c = getch();

		switch (c)
		{
			case 'h':
				locj--;
				if (locj < 0)
				{
					locj == jc - 1;
				}
				break;
			case 'l':
				locj++;
				if (locj >= jc)
				{
					locj = 0;
				}
				break;
			case 'j':
				loci++;
				if (loci >= ic)
				{
					loci = 0;
				}
				break;
			case 'k':
				loci--;
				if (loci < 0)
				{
					loci = ic - 1;
				}
				break;
			case 's':
				if (f[loci][locj] == -1)
				{
					f[loci][locj] = 9;
					bombc--;
				}
				else if (f[loci][locj] == 9)
				{
					f[loci][locj] = -1;
					bombc++;
				}
				break;
			case 'd':
				if (f[loci][locj] == 9)
				{
					break;
				}

				if (nums[loci + 1][locj + 1] == -1)
				{
					c = 'q';
					break;
				}
				if (f[loci][locj] == -1)
				{
					if (nums[loci + 1][locj + 1] == 0)
					{
						bucket_fill_zeros(&(f[0][0]), &(nums[0][0]), ic, jc, loci, locj);
					}
					else
					{
						f[loci][locj] = nums[loci + 1][locj + 1];
					}
				}
				else
				{
					c = getch();
					if (c != 'd')
					{
						break;
					}

					for (i = -1; i < 2; i++)
					{
						for (j = -1; j < 2; j++)
						{
							if (loci + i >= 0 && loci + i < ic && locj + j >= 0 && locj + j < jc)
							{
								if (f[loci + i][locj + j] == 9)
								{
									continue;
								}
								if (nums[loci + 1 + i][locj + 1 + j] == -1)
								{
									c = 'q';
									break;
								}
								if (f[loci + i][locj + j] == -1)
								{
									if (nums[loci + 1 + i][locj + 1 + j] == 0)
									{
										bucket_fill_zeros(&(f[0][0]), &(nums[0][0]), ic, jc, loci + i, locj + j);
									}
									else
									{
										f[loci + i][locj + j] = nums[loci + 1 + i][locj + 1 + j];
									}
								}
							}
						}
					}
				}
				break;
		}

		for (i = 0; i < ic; i++)
		{
			for (j = 0; j < jc; j++)
			{
				if (f[i][j] == -1)
				{
					break;
				}
			}
			if (j != jc)
			{
				break;
			}
		}
		if (i == ic)
		{
			mvprintw(1, 0, "+----------------+");
			mvprintw(2, 0, "| WINNER WINNER  |");
			mvprintw(3, 0, "| CHICKEN DINNER |");
			mvprintw(4, 0, "+----------------+");
			refresh();
			getch();
			break;
		}

		if (c == 'q')
		{
			mvprintw(1, 0, "+------------+");
			mvprintw(2, 0, "| GAME OVER! |");
			mvprintw(3, 0, "+------------+");
			refresh();
			getch();
			break;
		}
	}





	clear();
	refresh();
	endwin();
	refresh();
}
