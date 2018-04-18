#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <time.h>

#define LOWER_BORDER 2
#define UPPER_BORDER 2
#define RIGHT_BORDER 7
#define LEFT_BORDER  7

int stack_arr_s1;
int stack_arr_s2;
void play();
void clearShadow();
void removeLinesColor();
void fillColor();
char cmove;
int find3y_(int game_[stack_arr_s1][stack_arr_s2]);
int find3x_(int game_[stack_arr_s1][stack_arr_s2]);
int find3y_game();
int find3x_game();
int findlimitx0(int** game);
int findlimitx1(int** game);
int findlimity0(int** game);
int findlimity1(int** game);
void rotate();
void moveLeft();
void moveRight();
void moveDown();
void moveUp();
void insert(int k);
void fisherYates(int* a,int l);
int choose();
void findShadow();
int findLengthDown(int y, int x);
void removeLines();
int checkLines();
int checkBottom();
int checkOnes();
void fill();
void drawAll();
void drawBoard();
void drawPieces();
void drawScore();
int** alloc_2d_int_array(int s1, int s2);
int*** alloc_3d_int_array(int s1, int s2, int s3);
void free_2d_int_array(int** a, int s1);
void free_3d_int_array(int*** a, int s1, int s2);
int gameOver();
void change_color_from_palette(int i);
void get_high_scores();
void save_high_scores();
void increase_score(int a);
void get_commands();
void game_mode();


int height;
int width;
int level             = 100;
int lines             = 10;
int linesTotal        = 200;
int levelNumber       = 0;
int lines_to_go;
int pieceBagRunner    = 100;
int upPress           = 0;
int downPress         = 0;
int spacePress        = 0;
int escPress          = 0;
int quit              = 0;
long leftTime         = 0;
long rightTime        = 0;
int linescores[]      = {400, 600, 2000, 9000};
int pieceBag[]        = {0, 1, 2, 3, 4, 5, 6};
int high_score[]      = {0, 0, 0, 0, 0, 0};
int score_loc;
int nextpiece;
int currentpiece;
int pieceColor;
int nextPieceColor;
int tetrisBonus       = 0;
int checkLinesLine    = 0;
int** gameShadow;
int** game;
int** gameColor;
int** rotate_piece;
int** rotate_temp;
int** game_temp;
int pieces_count      = 7;
int pieces_height     = 2;
int pieces_width      = 4;
int*** pieces;

int main()
{
	int i, j;
	WINDOW* win = initscr();
	curs_set(0);
	noecho();
	halfdelay(1);

	if (has_colors())
	{
		start_color();
		init_pair(0, COLOR_GREEN, COLOR_BLACK);
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_BLUE, COLOR_BLACK);
		init_pair(3, COLOR_CYAN, COLOR_BLACK);
		init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(5, COLOR_YELLOW, COLOR_BLACK);
		init_pair(6, COLOR_WHITE, COLOR_BLACK);
	}

	height       = 24;
	width        = 10;

	pieceColor        = currentpiece + 1;
	nextPieceColor    = nextpiece + 1;

	pieces     = alloc_3d_int_array(7, 2, 4);
	pieces[0][0][0] = 1;
	pieces[0][0][1] = 3;
	pieces[0][0][2] = 1;
	pieces[0][0][3] = 0;
	pieces[0][1][0] = 1;
	pieces[0][1][1] = 0;
	pieces[0][1][2] = 0;
	pieces[0][1][3] = 0;
	
	pieces[1][0][0] = 1;
	pieces[1][0][1] = 3;
	pieces[1][0][2] = 1;
	pieces[1][0][3] = 0;
	pieces[1][1][0] = 0;
	pieces[1][1][1] = 0;
	pieces[1][1][2] = 1;
	pieces[1][1][3] = 0;

	pieces[2][0][0] = 1;
	pieces[2][0][1] = 3;
	pieces[2][0][2] = 1;
	pieces[2][0][3] = 0;
	pieces[2][1][0] = 0;
	pieces[2][1][1] = 1;
	pieces[2][1][2] = 0;
	pieces[2][1][3] = 0;
	
	pieces[3][0][0] = 1;
	pieces[3][0][1] = 3;
	pieces[3][0][2] = 0;
	pieces[3][0][3] = 0;
	pieces[3][1][0] = 0;
	pieces[3][1][1] = 1;
	pieces[3][1][2] = 1;
	pieces[3][1][3] = 0;
	
	pieces[4][0][0] = 0;
	pieces[4][0][1] = 3;
	pieces[4][0][2] = 1;
	pieces[4][0][3] = 0;
	pieces[4][1][0] = 1;
	pieces[4][1][1] = 1;
	pieces[4][1][2] = 0;
	pieces[4][1][3] = 0;

	pieces[5][0][0] = 1;
	pieces[5][0][1] = 3;
	pieces[5][0][2] = 1;
	pieces[5][0][3] = 1;
	pieces[5][1][0] = 0;
	pieces[5][1][1] = 0;
	pieces[5][1][2] = 0;
	pieces[5][1][3] = 0;

	pieces[6][0][0] = 0;
	pieces[6][0][1] = 1;
	pieces[6][0][2] = 1;
	pieces[6][0][3] = 0;
	pieces[6][1][0] = 0;
	pieces[6][1][1] = 1;
	pieces[6][1][2] = 1;
	pieces[6][1][3] = 0;



	game       = alloc_2d_int_array(height + 1, width);
	game_temp  = alloc_2d_int_array(height + 1, width);
	gameShadow = alloc_2d_int_array(height + 1, width);
	gameColor  = alloc_2d_int_array(height + 1, width);

	for (i = 0; i < height; i++)
	for (j = 0; j < width; j++)
	{
		game[i][j] = 0;
		gameShadow[i][j] = 0;
		game_temp[i][j] = 0;
		gameColor[i][j] = 0;
	}

	for (i = 0; i < width; i++)
	{
		game[height][i] = 5;
	}

	currentpiece = choose();
	nextpiece = choose();

	game_mode();

	clear();
	endwin();
	refresh();
	free_3d_int_array(pieces, 2, 4);
	free_2d_int_array(game, width);
	free_2d_int_array(game_temp, width);
	free_2d_int_array(game, width);
	free_2d_int_array(gameColor, width);
}

void game_mode()
{
	int i;
	leftTime  = 0;
	rightTime = 0;

	for (i = 0; i < width; i++)
	{
		gameColor[height - 1][i] = 5;
	}

	level        = 100;
	lines        = 10;
	linesTotal   = 200;
	levelNumber  = 0;

	while (!gameOver() && levelNumber < 20)
	{
		int cc = 0;

		if (checkBottom())
	   	{
			fillColor();
		   	currentpiece = nextpiece;
		   	nextpiece = choose(); 
			pieceColor = currentpiece + 1;
		   	nextPieceColor = nextpiece + 1;
		   	fill();
		   	if (gameOver())
			{
				break;
			}
		}
		else
		{
			moveDown();
		}

		for (i = 0; i < 4; i++)
		{
			if (checkLines() != -1)
			{
				if (tetrisBonus)
				{
					increase_score(12000*levelNumber);
				}
				checkLinesLine = checkLines();
				removeLines();
				removeLinesColor();
				increase_score(linescores[i]*(1 + levelNumber));
				if (i == 3)
				{
					tetrisBonus = 1;
				}
				else
				{
					tetrisBonus = 0;
				}
				linesTotal--;
				if (linesTotal%10 > lines || linesTotal%10 == 0)
				{
					levelNumber++; level -= 5;
				}
				lines = linesTotal%10;
				if (lines == 0)
				{
					lines = 10;
				}
				if (lines > 0 && levelNumber == 20)
				{
					lines = 0;
				}
			}
		}


		if (!checkOnes())
		{
			insert(currentpiece);
			if (gameOver())
			{
				break;
			}
		}

		while (cc*4 < level)
		{
			if (levelNumber > 19)
			{
				break;
			}
			clearShadow();
			drawAll();

			cmove = getch();
			if (cmove == 'q')
			{
				mvaddch(10, 10, 'B');
				levelNumber = 20;
			}

			if (!spacePress && cmove == ' ')
			{
				mvaddch(10, 10, 'B');
				while(!checkBottom())
				{
					moveDown();
					increase_score(8*(1 + levelNumber));
				}
				spacePress = 1;
				break;
			}

			if (cmove == 'j')
			{
				moveLeft();
			}

			if (cmove == 'l')
			{
				moveRight();
			}

			if (!upPress && cmove == 'i')
			{
				rotate();
				upPress = 1;
			}

			if (cmove == 'k')
			{
				mvaddch(10, 10, 'D');
				cc += 15;
				increase_score(1 + levelNumber);
			}

			if (cmove == 'p')
			{
				mvaddch(10, 10, 'P');
				/* DO PAUSE IS EZ I KNOW HAUH */
			}

			refresh(); /* TODO DELETE */

			cc++;
			if (cmove != ' ')
			{
				spacePress = 0;
			}
			if (cmove != 'j');
			{
				downPress = 0;
			}
			if (cmove != 'k')
			{
				upPress = 0;
			}
		}
	}
}

void clearShadow()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			gameShadow[i][j] = 0;
}

void removeLinesColor()
{
	int i, j;
	for (i = 0; i < width; i++)
		gameColor[checkLinesLine][i] = 0;

	for (i = checkLinesLine; i > 0; i--)
		for (j = 0; j < width; j++)
			gameColor[i][j] = gameColor[i - 1][j];
}

void fillColor()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1 || game[i][j] == 3)
				gameColor[i][j] = currentpiece;
}

int find3x_(int game_[stack_arr_s1][stack_arr_s2])
{
	int i, j;
	for (i = 0; i < stack_arr_s1; i++)
		for (j = 0; j < stack_arr_s2; j++)
			if  (game_[i][j] == 3) return j;

	return -1;
}

int find3y_(int game_[stack_arr_s1][stack_arr_s2])
{
	int i, j;
	for (i = 0; i < stack_arr_s1; i++)
		for (j = 0; j < stack_arr_s2; j++)
			if  (game_[i][j] == 3) return i;

	return -1;
}

int find3x_game()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 3) return j;

	return -1;
}

int find3y_game()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 3) return i;

	return -1;
}

int findlimitx0(int** game)
{
	int i, j;
	for (j = 0; j < width; j++)
		for (i = 0; i < height; i++)
			if  (game[i][j] == 1 || game[i][j] == 3) return j;

	return -1;
}

int findlimitx1(int** game)
{
	int i, j;
	for (j = width - 1; j >= 0; j--)
		for (i = height - 1; i >= 0; i--)
			if  (game[i][j] == 1 || game[i][j] == 3) return j;

	return -1;
}

int findlimity0(int** game)
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1 || game[i][j] == 3) return i;

	return -1;
}

int findlimity1(int** game)
{
	int i, j;
	for (i = height - 1; i >= 0; i--)
		for (j = width - 1; j >= 0; j--)
			if  (game[i][j] == 1 || game[i][j] == 3) return i;

	return -1;
}

void rotate()
{
	//TODO
	//
	//         o
	//         ooo
	//      oo   xx
	//       oo   x
	//            x
	int i, j;
	int move        = 0;
	int gamepieceX0 = findlimitx0(game);
	int gamepieceY0 = findlimity0(game);
	int gamepieceX1 = findlimitx1(game);
	int gamepieceY1 = findlimity1(game);

	int pieceWidth  = gamepieceX1 - gamepieceX0 + 1;
	int pieceHeight = gamepieceY1 - gamepieceY0 + 1;

	int piece[pieceHeight][pieceWidth];
	int temp[pieceWidth][pieceHeight];

	for (i = 0; i < pieceHeight; i++)
		for (j = 0; j < pieceWidth;  j++)
		{
			piece[i][j] = 0;
			temp[j][i]  = 0;
		}



	for (i = gamepieceY0; i <= gamepieceY1; i++)
		for (j = gamepieceX0; j <= gamepieceX1; j++)
			if  (game[i][j] == 1 || game[i][j] == 3)
				piece[i - gamepieceY0][j - gamepieceX0] = game[i][j];

	for (i = 0; i < pieceWidth;  i++)
		for (j = 0; j < pieceHeight; j++)
			temp[i][j] = piece[pieceHeight - 1 - j][i];


	int game3x = find3x_game();
	int game3y = find3y_game();
	stack_arr_s1 = pieceWidth;
	stack_arr_s2 = pieceHeight;
	int temp3x = find3x_(temp);
	int temp3y = find3y_(temp);

	if (pieceWidth == 2 && pieceHeight == 2) return;

	while (game3y < temp3y)
	{
		int gamey1 = game3y;
		int tempy1 = temp3y;

		moveDown();

		stack_arr_s1 = pieceWidth;
		stack_arr_s2 = pieceHeight;
		game3y = find3y_game();
		temp3y = find3y_(temp);

		if (game3y - temp3y == gamey1 - tempy1) return;
	}

	while (game3y + pieceWidth - temp3y > height)
	{
		int gamey1 = game3y;
		int tempy1 = temp3y;

		moveUp();

		stack_arr_s1 = pieceWidth;
		stack_arr_s2 = pieceHeight;
		game3y = find3y_game();
		temp3y = find3y_(temp);

		if (game3y == gamey1 && temp3y == tempy1) return;
	}

	if (pieceWidth == 1)
	{
		if (game3y < height/2)
		{
			if      (game3x == 0                  && game[game3y + 2][game3x] == 1) {move += 2; moveRight(); moveRight();}
			else if (game3x == 0                  && game[game3y + 2][game3x] != 1) {move += 1; moveRight();}
			else if (game3x == 1                  && game[game3y + 2][game3x] == 1) {move += 1; moveRight();}
			else if (game3x == width - 1 && game[game3y + 2][game3x] != 1) {move -= 2; moveLeft(); moveLeft();}
			else if (game3x == width - 1 && game[game3y + 2][game3x] == 1) {move -= 1; moveLeft();}
			else if (game3x == width - 2 && game[game3y + 2][game3x] != 1) {move -= 1; moveLeft();}
		}
		else
		{ 
			if      (game3x == 0                  && game[game3y - 2][game3x] != 1) {move += 2; moveRight(); moveRight();}
			else if (game3x == 0                  && game[game3y - 2][game3x] == 1) {move += 1; moveRight();}
			else if (game3x == 1                  && game[game3y - 2][game3x] != 1) {move += 1; moveRight();}
			else if (game3x == width - 1 && game[game3y - 2][game3x] == 1) {move -= 2; moveLeft(); moveLeft();}
			else if (game3x == width - 1 && game[game3y - 2][game3x] != 1) {move -= 1; moveLeft();}
			else if (game3x == width - 2 && game[game3y - 2][game3x] == 1) {move -= 1; moveLeft();}
		}
	}
	else
	{
		while (game3x < temp3x)
		{
			int gamex1 = game3x;

			moveRight();
			if (game3x == find3x_game()) moveLeft();

			stack_arr_s1 = pieceWidth;
			stack_arr_s2 = pieceHeight;
			game3x = find3x_game();
			temp3x = find3x_(temp);

			if (game3x == gamex1) return;
		}

		while (game3x + pieceHeight - temp3x > width)
		{
			int gamex1 = game3x;

			moveLeft();
			if (game3x == find3x_game()) moveRight();

			stack_arr_s1 = pieceWidth;
			stack_arr_s2 = pieceHeight;
			game3x = find3x_game();
			temp3x = find3x_(temp);

			if (game3x == gamex1) return;
		}
	}

	int game3xnew = find3x_game();
	int game3ynew = find3y_game();

	if (game3ynew - temp3y < 0 || game3ynew - temp3y > height - 1 || game3xnew - temp3x < 0 || game3xnew - temp3x + pieces_height > width)
	{
		while (game3x != find3x_game())
		{
			if (move <  0) moveRight();
			if (move  > 0) moveLeft();
			if (move == 0) break;
		}
		return;
	}

	for (i = game3ynew - temp3y; i < game3ynew - temp3y + pieceWidth; i++)
		for (j = game3xnew - temp3x; j < game3xnew - temp3x + pieceHeight; j++)
			if  ((game[i][j] == 2 || game[i][j] == 5) && (temp[i - game3ynew + temp3y][j - game3xnew + temp3x] == 3 || temp[i - game3ynew + temp3y][j - game3xnew + temp3x] == 1))
				return;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1 || game[i][j] == 3) game[i][j] = 0;

	for (i = game3ynew - temp3y; i < game3ynew - temp3y + pieceWidth; i++)
		for (j = game3xnew - temp3x; j < game3xnew - temp3x + pieceHeight; j++)
			if  (temp[i - game3ynew + temp3y][j - game3xnew + temp3x] == 1 || temp[i - game3ynew + temp3y][j - game3xnew + temp3x] == 3)
				game[i][j] = temp[i - game3ynew + temp3y][j - game3xnew + temp3x];
}

void moveLeft()
{
	int i, j;
	for (i = 0; i < height; i++)
		if  (game[i][0] == 1 || game[i][0] == 3) return;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			game_temp[i][j] = 0;
			if  (game[i][j] == 1 && game[i][j - 1] == 2) return;
			if  (game[i][j] == 3 && game[i][j - 1] == 2) return;
		}


	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game[i][j] == 1) game_temp[i][j - 1] = 1;
			if  (game[i][j] == 3) game_temp[i][j - 1] = 3;
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if (game[i][j] == 1 || game[i][j] == 3) game[i][j] = 0;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game_temp[i][j] == 1 || game_temp[i][j] == 3)
			{
				game[i][j] = game_temp[i][j];
				game_temp[i][j] = 0;
			}
		}
}

void moveRight()
{
	int i, j;
	for (i = 0; i < height; i++)
		if  (game[i][width-1] == 1 || game[i][width-1] == 3) return;

	for (i = 0; i < height; i++)
		for (j = 0; j < width - 1; j++)
		{
			game_temp[i][j] = 0;
			if  (game[i][j] == 1 && game[i][j + 1] == 2) return;
			if  (game[i][j] == 3 && game[i][j + 1] == 2) return;
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game[i][j] == 1) game_temp[i][j + 1] = 1;
			if  (game[i][j] == 3) game_temp[i][j + 1] = 3;
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if (game[i][j] == 1 || game[i][j] == 3) game[i][j] = 0;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game_temp[i][j] == 1 || game_temp[i][j] == 3)
			{
				game[i][j] = game_temp[i][j];
				game_temp[i][j] = 0;
			}
		}
}

void moveDown()
{
	int i, j;
	if (checkBottom()) return;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game[i][j] == 1) game_temp[i + 1][j] = 1;
			if  (game[i][j] == 3) game_temp[i + 1][j] = 3;
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1 || game[i][j] == 3) game[i][j] = 0;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game_temp[i][j] == 1 || game_temp[i][j] == 3)
			{
				game[i][j] = game_temp[i][j];
				game_temp[i][j] = 0;
			}
		}
}

void moveUp()
{
	int i, j;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			game_temp[i][j] = 0;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game[i][j] == 1) game_temp[i - 1][j] = 1;
			if  (game[i][j] == 3) game_temp[i - 1][j] = 3;
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1 || game[i][j] == 3) game[i][j] = 0;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game_temp[i][j] == 1 || game_temp[i][j] == 3)
			{
				game[i][j] = game_temp[i][j];
				game_temp[i][j] = 0;
			}
		}
}

void insert(int k)
{
	int i, j;
	int s = (width - 4)/2;

	for (i = 0; i < pieces_height; i++)
		for (j = 0; j < pieces_width; j++)
		{
			if ((pieces[k][i][j] == 1 || pieces[k][i][j] == 3) && game[i][j + s] == 2) game[height - 1][0] = 9;
			if  (pieces[k][i][j] == 1 || pieces[k][i][j] == 3) game[i][j + s] = pieces[k][i][j];
		}
}

void fisherYates(int* a,int l)
{
	int i;
	for (i = 0; i < l - 1; i++)
	{
		int t = (rand()%(l - i)) + i;

		int tmp = a[i];
		a[i] = a[t];
		a[t] = tmp;
	}
}

int choose()
{
	if (pieceBagRunner > 6)
	{
		fisherYates(pieceBag, 7);
		pieceBagRunner = 0;
	}

	return pieceBag[pieceBagRunner++];
}

/* */
void findShadow()
{
	int i, j;
	int gamepieceX0 = findlimitx0(game);
	int gamepieceY0 = findlimity0(game);
	int gamepieceX1 = findlimitx1(game);
	int gamepieceY1 = findlimity1(game);

	int pieceWidth  = gamepieceX1 - gamepieceX0 + 1;
	int pieceHeight = gamepieceY1 - gamepieceY0 + 1;

	/* 
	   for (i = 0; i < height; i++)
	   {
	   for (j = 0; j < width;  j++)
	   {
	   printf("%d", gameShadow[i][j]);
	   gameShadow[i][j] = 0;
	   }
	   printf("\n");
	   }
	/* */

	if (gamepieceX0 == -1) return;
	if (gamepieceX1 == -1) return;
	if (gamepieceY0 == -1) return;
	if (gamepieceY1 == -1) return;

	int piece[pieceHeight][pieceWidth];

	for (i = gamepieceY0; i <= gamepieceY1; i++)
		for (j = gamepieceX0; j <= gamepieceX1; j++)
		{
			if  (game[i][j] == 1 || game[i][j] == 3)
				piece[i - gamepieceY0][j - gamepieceX0] = game[i][j];
			else	
				piece[i - gamepieceY0][j - gamepieceX0] = 0;
		}
	int lengths[pieceWidth];
	for (i = 0; i < pieceHeight; i++)
		for (j = 0; j < pieceWidth;  j++)
			if  (piece[i][j] == 1 || piece[i][j] == 3)
				lengths[j] = findLengthDown(gamepieceY0 + i, gamepieceX0 + j);

	int min = lengths[0];

	for (i = 1; i < pieceWidth; i++)
		if  (lengths[i] < min) min = lengths[i];

	for (i = 0; i < pieceHeight; i++)
		for (j = 0; j < pieceWidth;  j++)
			if  (piece[i][j] == 1 || piece[i][j] == 3)
				gameShadow[gamepieceY0 + min + i][gamepieceX0 + j] = 1;

	/* 
	   for (i = 0; i < height; i++)
	   {
	   for (j = 0; j < width;  j++)
	   {
	   printf("%d", gameShadow[i][j]);
	   }
	   printf("\n");
	   }
	/* */
}
/* */

/* CHAGNED */
int findLengthDown(int y, int x)
{
	int i;

	for (i = 1; game[y + i][x] != 2 && game[y + i][x] != 5; i++) { }

	return i - 1;
}

void removeLines()
{
	int i, j;
	for (i = 0; i < width; i++)
		game[checkLinesLine][i] = 0;

	for (i = checkLinesLine; i > 0; i--)
		for (j = 0; j < width; j++)
			game[i][j] = game[i - 1][j];

	for (i = 0; i < width; i++)
		game[0][i] = 0;
}

/*
   int checkLines()
   {
   int i, j;
   for (i = 0; i < height; i++)
   {
   int test = 1;

   for (j = 0; j < width; j++)
   test = test && game[i][j] == 2;

   if  (test) return i;
   }

   return -1;
   }
/* */

/* CHANGED */
int checkLines()
{
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
			if (game[i][j] != 2) break;
		if (j == width) return i;
	}
	return -1;
}

int checkBottom()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if  (game[i][j] == 1 && game[i + 1][j] == 2) return 1;
			if  (game[i][j] == 1 && game[i + 1][j] == 5) return 1;
			if  (game[i][j] == 3 && game[i + 1][j] == 2) return 1;
			if  (game[i][j] == 3 && game[i + 1][j] == 5) return 1;
		}
	return 0;
}

/* TODO */
/* Betra að hafa insert-flag en nenni ekki núna */
int checkOnes()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1) return 1;
	return 0;
}

void fill()
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if  (game[i][j] == 1 || game[i][j] == 3)
				game[i][j] = 2;
}

void drawAll()
{
	clear();
	drawBoard();
	drawPieces();
	//drawScore();
	refresh();
}

void drawScore()
{
	/* */
}

void drawBoard()
{
	move(0, 0);
	change_color_from_palette(6);
	printw("    xxxxxxxxxxxxxxxx    \n");
	printw(" xxxxxxxxxxxxxxxxxxxxxx \n");
	printw("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw("x                      x           x\n");
	printw("x                      x           x\n");
	printw("x                      x           x\n");
	printw("x                      x           x\n");
	printw("x                      x           x\n");
	printw("x                      xxxxxxxxxxxxx\n");
	printw("x                      xxxx\n");
	printw("x                      xx\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("x                      x\n");
	printw("xxxxxxxxxxxxxxxxxxxxxxxx\n");
	printw(" xxxxxxxxxxxxxxxxxxxxxx \n");
	printw("    xxxxxxxxxxxxxxxx    \n");
}

void drawPieces()
{
	int i, j;
	findShadow();

	for (i = 0; i < pieces_height; i++)
	{
		for (j = 0; j < pieces_width; j++)
		{
			if  (pieces[nextpiece][i][j] == 1 || pieces[nextpiece][i][j] == 3)
			{
				change_color_from_palette(nextpiece);
				mvaddch(4 + i, 27 + j*2, 'x');
			}
		}
	}



	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (gameShadow[i][j] == 1)
			{
				change_color_from_palette(currentpiece);
				mvaddch(3 + i, 2 + j*2, '.');
			}

			if (game[i][j] == 1 || game[i][j] == 3)
			{
				change_color_from_palette(currentpiece);
				mvaddch(3 + i, 2 + j*2, 'o');
			}

			if (game[i][j] == 2)
			{
				change_color_from_palette(gameColor[i][j]);
				mvaddch(3 + i, 2 + j*2, 'x');
			}
		}
	}
}

void change_color_from_palette(int i)
{
	attron(COLOR_PAIR(i + 1));
}

int** alloc_2d_int_array(int s1, int s2)
{
	int i, j;
	int** ret = malloc(s1*sizeof(int*));

	for (i = 0; i < s1; i++)
	{
		ret[i] = malloc(s2*sizeof(int));
		for (j = 0; j < s2; j++) ret[i][j] = 0;
	}

	return ret;
}

int*** alloc_3d_int_array(int s1, int s2, int s3)
{
	int i;
	int*** ret = malloc(s1*sizeof(int**));
	for (i = 0; i < s1; i++) ret[i] = alloc_2d_int_array(s2, s3);

	return ret;
}

void free_2d_int_array(int** a, int s1)
{
	int i;
	for (i = 0; i < s1; i++) free(a[i]);

	free(a);
}

void free_3d_int_array(int*** a, int s1, int s2)
{
	int i;
	for (i = 0; i < s2; i++) free_2d_int_array(a[i], s1);

	free(a);
}


int gameOver()
{
	int i;
	for (i = (width - 4)/2; i < (width - 4)/2 + 4 ; i++)
		if (game[0][i] == 2) return 1;

	if (game[height - 1][0] == 9) return 1;

	return 0;
}

void increase_score(int a)
{
	high_score[score_loc] += a;

	while (score_loc > 0 && high_score[score_loc - 1] < high_score[score_loc])
	{
		int tmp = high_score[score_loc - 1];
		high_score[score_loc - 1] = high_score[score_loc];
		high_score[score_loc] = tmp;

		score_loc--;
	}
}
