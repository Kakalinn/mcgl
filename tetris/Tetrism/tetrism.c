#include <stdlib.h>
#include <stdio.h>
#include "draw.h"
#include "clock.h"
#include "blsl.h"
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
void game_mode_1();
void game_mode_2();
void game_mode_3();
void game_mode_4();
void game_mode_5();


int height;
int width;
int gamemode;
int seed_type         = 0;
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
FILE* piece_file;


int main()
{
	height       = 24;
	width        = 10;
	gamemode     = 1;  

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


	get_commands();



	free_3d_int_array(pieces, 2, 4);
	//printf("ret\n");
	//return;
}

void get_commands()
{
	int i;
	char c;
	char fn[] = "saves/hs-~-~~~-~~~";


	
	//Poll for inputs of the stdin
	printf("c -> Change gamemode\n");
	printf("  1 -> \"Normal\" mode. Every ten rows the level\n");
	printf("       increments. Try to beat the highscore in 20\n");
	printf("       levels\n");
	printf("  2 -> Clear 40 lines as fast as possible. Consant\n");
	printf("       speed, exponential fun.\n");
	printf("\n");
	printf("h -> Set the height of the game\n");
	printf("  <int> -> Sets <int> as the height\n");
	printf("\n");
	printf("w -> Set the width of the game\n");
	printf("  <int> -> Sets <int> as the width\n");
	printf("\n");
	printf("p -> Prints the highscore for the current settings\n");
	printf("\n");
	printf("g -> GO! Plays the game with the select parameters\n");
	printf("\n");
	printf("q -> Quits the game\n");
	printf("\n");

	printf("Default parameters:\n");
	printf("  c -> 1\n");
	printf("  s -> 1\n");
	printf("  h -> 24\n");
	printf("  w -> 10\n");



	while (1)
	{
		int _val;
		c = getchar();
		//while (getchar() != '\n') { }

		switch (c)
		{
			case 'c':
			c = getchar();
			while (getchar() != '\n') { }

			switch (c)
			{
				case '1':
				gamemode = 1;
				printf("~>Gamemode set to 1.\n");

				break;
				case '2':
				gamemode = 2;
				printf("~>Gamemode set to 2.\n");


				break;
				default:
				printf("~>Invalid gamemode!\n");
			}

			break;
			case 'h':
			c = getchar();
			_val = 0;
			while (c != '\n')
			{
				_val = _val*10 + c - 48;				
				c = getchar();
			}

			if (_val == 0)
			{
				printf("~>Height is %d\n", height);
			}
			else
			{
				height = _val;
				printf("~>height has been set to %d.\n", _val);
			}

			break;
			case 'w':
			c = getchar();
			_val = 0;
			while (c != '\n')
			{
				_val = _val*10 + c - 48;				
				c = getchar();
			}

			if (_val == 0)
			{
				printf("~>Width is %d\n", width);
			}
			else
			{
				width = _val;
				printf("~>width has been set to %d.\n", _val);
			}

			break;
			case 's':
			switch (getchar())
			{
				case '1':
				seed_type = 1;
				printf("~>The ssed mode has been set to 1.\n");
				break;

				case '2':
				seed_type = 2;
				printf("~>The ssed mode has been set to 2.\n");
				break;

				case '3':
				seed_type = 3;
				printf("~>The ssed mode has been set to 3.\n");
				break;

				case '\n':
				printf("~>Seed mode is set to %d.\n", seed_type);
				goto seed_type_skip;

				default:
				printf("~>Invalid seed mode.\n");
			}
			while (getchar() != '\n') { }
			seed_type_skip:

			break;
			case 'p':
			fn[9]   = gamemode + 48;

			fn[11]  = width/100 + 48;
			fn[12]  = (width%100)/10 + 48;
			fn[13]  = width%10 + 48;

			fn[15]  = height/100 + 48;
			fn[16]  = (height%100)/10 + 48;
			fn[17]  = height%10 + 48;
			FILE* fp = fopen(fn, "r");
			//printf("Reading from file %s\n", fn);
			for (i = 0; i < 5; i++)
			{
				printf("~>%d: ", i + 1);
				char temp = fgetc(fp);
				while (temp != '\n')
				{
					putchar(temp);
					temp = fgetc(fp);
				}
				putchar('\n');
			}

			break;

			//Load level from file
			case 'l':
			c = getchar();
			while (c == ' ' || c == '\t' || c == '\n') c = getchar();

			char fn[35];
			fn[0] = 'l';
			fn[1] = 's';
			fn[2] = '/';
			fn[3] = c;

			for (i = 4; i < 35; i++)
			{
				fn[i] = getchar();
				if (fn[i] == '\n') break;
			}
			fn[i] = '\0';

			printf("~>Loading %s\n", fn);
			int err = blsl_gen(fn, "pif");
			if (err == -1)
			{
				printf("~>Load failed. %s not found.\n", fn);
			}
			else if (err == -2)
			{
				printf("~>Load failed. Syntax error in %s, see blsl_syntax.txt.\n", fn);
			}
			else printf("~>Loaded\n");







			break;
			case 'g':
			play();
			//printf("out of play1\n");
			break;

			case 'q':
			printf("~>ggwp\n");
			//printf("This will exit the loop when it's good and ready.\n");
			//break; /*Comment or remove this line when it's good and ready*/
			return;
		}
	}

}

void play()
{
	int i, j;
	draw_set_coord_size(width + RIGHT_BORDER + LEFT_BORDER, height + UPPER_BORDER + LOWER_BORDER);
	draw_init((width + RIGHT_BORDER + LEFT_BORDER)*600/(height + UPPER_BORDER + LOWER_BORDER), 600);

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
	game[height][i] = 5;

	if (seed_type == 3)
	{
		piece_file = fopen("pif", "r");
	}

	currentpiece      = choose();
	nextpiece         = choose();

	int should_save = 1;
	get_high_scores();
	/*  PLAY  */
	switch (gamemode)
	{
		case 1:
		score_loc = 5;
		game_mode_1();
		break;
		case 2:
		score_loc = 0;
		game_mode_2();
		if (lines_to_go > 0) should_save = 0;
		break;
	}
	/* NO PLAY */

	printf("~>Your score was %d", high_score[score_loc]);
	if (gamemode == 2) printf("ms");
	printf(".\n");




	if (seed_type == 3)
	{
		printf("~>Your score will not be saved because you are using seed mode 3. Change the seed mode to achieve valid highscores.\n");
		fclose(piece_file);
	}
	else
	{
		if (should_save && score_loc != 5)
		{
			save_high_scores();
			printf("~>Congratulations on your high score. You scored the ");
			switch (score_loc)
			{
				case '4':
				printf("5th ");
				break;
				case '3':
				printf("4th ");
				break;
				case '2':
				printf("3rd ");
				break;
				case '1':
				printf("2nd ");
				break;
			}
			printf("highest score on this specific setup.\n");

		}

	}
	
	free_2d_int_array(game, width);
	free_2d_int_array(game_temp, width);
	free_2d_int_array(game, width);
	free_2d_int_array(gameColor, width);




	draw_end();
}

void game_mode_1()
{
	int i;
	leftTime  = 0;
	rightTime = 0;

	draw_wait(10);

	for (i = 0; i < width; i++)
	gameColor[height - 1][i] = 5;

	level        = 100;
	lines        = 10;
	linesTotal   = 200;
	levelNumber  = 0;

	clock_start();
	int draw_time = clock_get();
	while (!gameOver() && levelNumber < 20 && !draw_should_close())
	{
		int cc = 0;

		if (checkBottom()) {fillColor(); currentpiece = nextpiece; nextpiece = choose(); 
			pieceColor = currentpiece + 1; nextPieceColor = nextpiece + 1; fill(); if (gameOver()) break;}
		else  moveDown();

		for (i = 0; i < 4; i++)
		if (checkLines() != -1)
		{
			if (tetrisBonus) increase_score(12000*levelNumber);
			checkLinesLine = checkLines();
			removeLines();
			removeLinesColor();
			increase_score(linescores[i]*(1 + levelNumber));
			if (i == 3) tetrisBonus = 1;
			else        tetrisBonus = 0;
			linesTotal--;
			if (linesTotal%10 > lines || linesTotal%10 == 0) {/*level_time[levelNumber] = clock_get();*/ levelNumber++; level -= 5;}
			lines = linesTotal%10;
			if (lines == 0) lines = 10;
			if (lines > 0 && levelNumber == 20) lines = 0;
		}


		if (!checkOnes()) {/*frequency[currentpiece]++;*/ insert(currentpiece); if (gameOver()) break;}

		while (cc < level && !draw_should_close())
		{
			if (levelNumber > 19) break;
			clearShadow();
			//level_frames[levelNumber]++;
			drawAll();

			draw_wait(10 - clock_get() + draw_time);
			draw_time = clock_get();

			draw_poll_events();
			if (!spacePress && draw_is_pressed(DRAW_KEY_SPACE))
			{
				while(!checkBottom())
				{
					moveDown();
					increase_score(8*(1 + levelNumber));
				}
				spacePress = 1;
				break;
			}

			if ((clock_get() - leftTime > 100) && draw_is_pressed(DRAW_KEY_LEFT) && !draw_is_pressed(DRAW_KEY_RIGHT))
			{
				leftTime = clock_get();
				moveLeft();
			}

			if ((clock_get() - rightTime > 100) && draw_is_pressed(DRAW_KEY_RIGHT) && !draw_is_pressed(DRAW_KEY_LEFT))
			{
				rightTime = clock_get();
				moveRight();
			}

			if (!upPress && draw_is_pressed(DRAW_KEY_UP))
			{
				rotate();
				upPress = 1;
			}

			if (draw_is_pressed(DRAW_KEY_DOWN))
			{
				cc += 15;
				increase_score(1 + levelNumber);
			}

			if (draw_is_pressed(DRAW_KEY_ESCAPE))
			{
				draw_change_color(0.0, 0.0, 0.0);
				draw_square_area(LEFT_BORDER, UPPER_BORDER, LEFT_BORDER + width, UPPER_BORDER + height);


				draw_square_area(LEFT_BORDER + width + 1, UPPER_BORDER, LEFT_BORDER + width + 6, UPPER_BORDER + 5);

				draw_change_color(1.0, 1.0, 0.0);
				draw_square(UPPER_BORDER + 1, LEFT_BORDER + width + 2);
				draw_square(UPPER_BORDER + 2, LEFT_BORDER + width + 2);
				draw_square(UPPER_BORDER + 3, LEFT_BORDER + width + 2);
				                                               
				draw_square(UPPER_BORDER + 1, LEFT_BORDER + width + 4);
				draw_square(UPPER_BORDER + 2, LEFT_BORDER + width + 4);
				draw_square(UPPER_BORDER + 3, LEFT_BORDER + width + 4);
				
				
				draw_swap_buffers();

				while (draw_is_pressed(DRAW_KEY_ESCAPE))
				{draw_poll_events();}
			
				
				while (1)
				{
					draw_poll_events();
					if (draw_is_pressed(DRAW_KEY_ESCAPE))
					{
						while (draw_is_pressed(DRAW_KEY_ESCAPE))
						{draw_poll_events();}

						break;
					}

					if (draw_is_pressed(DRAW_KEY_ENTER))
					{
						while (draw_is_pressed(DRAW_KEY_ENTER))
						{draw_poll_events();}

						quit = 1;
						return;
					}

				}
				draw_wait(500);
			}

			cc++;
			if (!draw_is_pressed(DRAW_KEY_SPACE))
			spacePress = 0;
			if (!draw_is_pressed(DRAW_KEY_DOWN))
			downPress  = 0;
			if (!draw_is_pressed(DRAW_KEY_UP))
			upPress    = 0;
		}
	}
	/*
	printf("Largest time between draws: %d\n", tempmax);
	printf("LevelNumber: %d\n", levelNumber);
	for (i = 0; i < levelNumber - 1; i++)
		level_time[levelNumber - i - 1] -= level_time[levelNumber - i - 2];

	
	for (i = 0; i < levelNumber; i++)
		printf("Level %d took %d seconds and %d frames were drawn (~%d FPS)\n", i + 1, level_time[i], level_frames[i], level_frames[i]/(level_time[i]/1000));
	/* */
}

void game_mode_2()
{
	int i;
	leftTime  = 0;
	rightTime = 0;

	draw_wait(10);

	for (i = 0; i < width; i++)
	gameColor[height - 1][i] = 5;

	clock_start();
	int draw_time  = clock_get();
	int pause_time = 0;
	lines_to_go = 10;
	while (!gameOver() && !draw_should_close())
	{
		increase_score(clock_get() - pause_time);
		int cc = 0;

		if (checkBottom()) {fillColor(); currentpiece = nextpiece; nextpiece = choose(); 
			pieceColor = currentpiece + 1; nextPieceColor = nextpiece + 1; fill(); if (gameOver()) break;}
		else  moveDown();

		/* */
		for (i = 0; i < 4; i++)
		{
			checkLinesLine = checkLines();
			int temp = checkLines();
			if (temp != -1)
			{
				removeLines();
				removeLinesColor();
				lines_to_go--;
				if (lines_to_go == 0) return;
			}
		}
		/* */

		if (!checkOnes()) {/*frequency[currentpiece]++;*/ insert(currentpiece); if (gameOver()) break;}

		while (cc < 50 && !draw_should_close())
		{
			clearShadow();
			drawAll();

			draw_wait(10 - clock_get() + draw_time);
			draw_time = clock_get();

			draw_poll_events();
			if (!spacePress && draw_is_pressed(DRAW_KEY_SPACE))
			{
				while(!checkBottom())
				{
					moveDown();
				}
				spacePress = 1;
				break;
			}

			if ((clock_get() - leftTime > 100) && draw_is_pressed(DRAW_KEY_LEFT) && !draw_is_pressed(DRAW_KEY_RIGHT))
			{
				leftTime = clock_get();
				moveLeft();
			}

			if ((clock_get() - rightTime > 100) && draw_is_pressed(DRAW_KEY_RIGHT) && !draw_is_pressed(DRAW_KEY_LEFT))
			{
				rightTime = clock_get();
				moveRight();
			}

			if (!upPress && draw_is_pressed(DRAW_KEY_UP))
			{
				rotate();
				upPress = 1;
			}

			if (draw_is_pressed(DRAW_KEY_DOWN))
			{
				cc += 15;
			}

			if (draw_is_pressed(DRAW_KEY_ESCAPE))
			{
				pause_time -= clock_get();
				draw_change_color(0.0, 0.0, 0.0);
				draw_square_area(LEFT_BORDER, UPPER_BORDER, LEFT_BORDER + width, UPPER_BORDER + height);


				draw_square_area(LEFT_BORDER + width + 1, UPPER_BORDER, LEFT_BORDER + width + 6, UPPER_BORDER + 5);

				draw_change_color(1.0, 1.0, 0.0);
				draw_square(UPPER_BORDER + 1, LEFT_BORDER + width + 2);
				draw_square(UPPER_BORDER + 2, LEFT_BORDER + width + 2);
				draw_square(UPPER_BORDER + 3, LEFT_BORDER + width + 2);
				                                               
				draw_square(UPPER_BORDER + 1, LEFT_BORDER + width + 4);
				draw_square(UPPER_BORDER + 2, LEFT_BORDER + width + 4);
				draw_square(UPPER_BORDER + 3, LEFT_BORDER + width + 4);
				
				
				draw_swap_buffers();

				while (draw_is_pressed(DRAW_KEY_ESCAPE))
				{draw_poll_events();}
			
				
				while (1)
				{
					draw_poll_events();
					if (draw_is_pressed(DRAW_KEY_ESCAPE))
					{
						while (draw_is_pressed(DRAW_KEY_ESCAPE))
						{draw_poll_events();}

						break;
					}

					if (draw_is_pressed(DRAW_KEY_ENTER))
					{
						while (draw_is_pressed(DRAW_KEY_ENTER))
						{draw_poll_events();}

						quit = 1;
						return;
					}

				}
				draw_wait(500);
				pause_time += clock_get();
			}

			cc++;
			if (!draw_is_pressed(DRAW_KEY_SPACE))
			spacePress = 0;
			if (!draw_is_pressed(DRAW_KEY_DOWN))
			downPress  = 0;
			if (!draw_is_pressed(DRAW_KEY_UP))
			upPress    = 0;
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
	//printf("TESTIN\n");
	if (seed_type == 1)
	{
		if (pieceBagRunner > 6)
		{
			fisherYates(pieceBag, 7);
			pieceBagRunner = 0;
		}

		return pieceBag[pieceBagRunner++];
	}
	if (seed_type == 2)
	{
		return rand()%7;
	}
	if (seed_type == 3)
	{
		char ret = fgetc(piece_file);
		while (ret == '\n' || ret == ' ' || ret == '\t' || ret == '\r') ret = fgetc(piece_file);
		if (ret == EOF)
		{
			//fseek(piece_file, SEEK_SET, 0);
			fseek(piece_file, 0 , SEEK_SET);
			ret = fgetc(piece_file);
		}

		switch (ret)
		{
			case 'l':
			return 0;
			case 'j':
			return 1;
			case 't':
			return 2;
			case 'z':
			return 3;
			case 's':
			return 4;
			case 'i':
			return 5;
			case 'o':
			return 6;
		}
	}
	//printf("TESTFUUUUUCK\n");
	return 0;
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
	/* 
	int i, j;
	printf("~\n");
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width;  j++)
			printf("%d", game[i][j]);
		printf("\n");
	}
	printf("~\n");
	/* */

	draw_clear();
	drawBoard();
	drawPieces();
	drawScore();
	draw_swap_buffers();	
}

void drawScore()
{
	float x1 = LEFT_BORDER  - 6.0;
	float x2 = LEFT_BORDER  - 1.0;
	float y1 = UPPER_BORDER + 1.0;
	float y2 = UPPER_BORDER + 2.0;
	draw_change_color(0.0, 0.0, 0.0);
	draw_square_area(x1 , y1, x2, y2 + 10.0);
	
	if (gamemode == 1)
	{
		if (score_loc == 0) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1,  x2, y2, 0.99999);

		if (score_loc == 1) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 2.0,  x2, y2 + 2.0, (float)high_score[1]/high_score[0]);

		if (score_loc == 2) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 4.0,  x2, y2 + 4.0, (float)high_score[2]/high_score[0]);

		if (score_loc == 3) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 6.0,  6.0, y2 + 6.0, (float)high_score[3]/high_score[0]);

		if (score_loc == 4) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 8.0, x2, y2 + 8.0, (float)high_score[4]/high_score[0]);

		if (score_loc == 5) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 10.0, x2, y2 + 10.0, (float)high_score[5]/high_score[0]);
	}
	if (gamemode == 2)
	{
		if (score_loc == 0) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1,  x2, y2, (float)high_score[0]/high_score[5]);

		if (score_loc == 1) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 2.0,  x2, y2 + 2.0, (float)high_score[1]/high_score[5]);

		if (score_loc == 2) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 4.0,  x2, y2 + 4.0, (float)high_score[2]/high_score[5]);

		if (score_loc == 3) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 6.0,  6.0, y2 + 6.0, (float)high_score[3]/high_score[5]);

		if (score_loc == 4) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 8.0, x2, y2 + 8.0, (float)high_score[4]/high_score[5]);

		if (score_loc == 5) draw_change_color(0.3, 0.3, 0.3);
		else                draw_change_color(1.0, 1.0, 1.0);
		draw_bar(x1, y1 + 10.0, x2, y2 + 10.0, 0.999999);
	}


	//TODO score, raptölur, tjékka hvort ég kláraði, gamemode 2 almennt










	/* 
	printf("Score 1.: %d\n", high_score[0]);
	printf("Score 2.: %d\n", high_score[1]);
	printf("Score 3.: %d\n", high_score[2]);
	printf("Score 4.: %d\n", high_score[3]);
	printf("Score 5.: %d\n", high_score[4]);
	printf("~~\n");
	/* */
}

void drawBoard()
{
	draw_change_color(0.4, 0.4, 0.4);
	//draw_square_area(1, 1, LEFT_BORDER + RIGHT_BORDER + width-1, UPPER_BORDER + LOWER_BORDER + height-1);
	draw_square_area(0, 0, LEFT_BORDER, height + UPPER_BORDER + LOWER_BORDER);
	draw_square_area(LEFT_BORDER + width, 0, LEFT_BORDER + RIGHT_BORDER + width, UPPER_BORDER + LOWER_BORDER + height);
	
	draw_square_area(LEFT_BORDER, 0, LEFT_BORDER + width, UPPER_BORDER);
	draw_square_area(LEFT_BORDER, UPPER_BORDER + height, LEFT_BORDER + width, UPPER_BORDER + LOWER_BORDER + height);
	//draw_square_area(LEFT_BORDER, 0, LEFT_BORDER + width, UPPER_BORDER);
	//
	draw_change_color(0.0, 0.0, 0.0);
	draw_square_area(LEFT_BORDER + width + 1, UPPER_BORDER , LEFT_BORDER + width + 6, UPPER_BORDER + 5);

	//draw_square_area(LEFT_BORDER, UPPER_BORDER + height, LEFT_BORDER + width, height + UPPER_BORDER + LOWER_BORDER);

	//draw_change_color(0, 0, 0);
	//draw_square_area(LEFT_BORDER + width + 1, 1, LEFT_BORDER + width + 6, 6);
}

void drawPieces()
{
	int i, j;
	findShadow();

	for (i = 0; i < pieces_height; i++)
	for (j = 0; j < pieces_width; j++)
	if  (pieces[nextpiece][i][j] == 1 || pieces[nextpiece][i][j] == 3)
	{
		change_color_from_palette(nextpiece);
		//draw_change_color(1.0, 1.0, 1.0);
		//draw_square(UPPER_BORDER + 7 + 2*cx3 - 2*i, LEFT_BORDER + width + 7 - 2*cy3 + 2*j);
		draw_square(UPPER_BORDER + 1 + i, LEFT_BORDER + width + 2 + j);
		draw_change_color(1.0, 1.0, 1.0);
		//draw_fill_square(LEFT_BORDER + width + 7 - 2*cy3 + 2*j, 7 + 2*cx3 - 2*i);
		draw_fill_square(UPPER_BORDER + 1 + i, LEFT_BORDER + width + 2 + j);
	}



	for (i = 0; i < height; i++)
	for (j = 0; j < width; j++)
	{
		if (gameShadow[i][j] == 1)
		{
			draw_change_color(0.05, 0.05, 0.05);
			draw_square(UPPER_BORDER + i, LEFT_BORDER + j);
		}

		if (game[i][j] == 1 || game[i][j] == 3)
		{
			change_color_from_palette(currentpiece);
			draw_square(UPPER_BORDER + i, LEFT_BORDER + j);
			draw_change_color(1.0, 1.0, 1.0);
			draw_fill_square(UPPER_BORDER + i, LEFT_BORDER + j);
		}

		if (game[i][j] == 2)
		{
			change_color_from_palette(gameColor[i][j]);
			draw_square(UPPER_BORDER + i, LEFT_BORDER + j);
			draw_change_color(0.67, 0.67, 0.67);
			draw_fill_square(UPPER_BORDER + i, LEFT_BORDER + j);
		}
	}
}

void change_color_from_palette(int i)
{
	//i = 0;
	switch (i)
	{
		case 0:
		draw_change_color(0.0, 0.0, 0.5);
		return;
		case 1:
		draw_change_color(1.0, 0.0, 1.0);
		return;
		case 2:
		draw_change_color(0.75, 0.75, 0.75);
		return;
		case 3:
		draw_change_color(1.0, 1.0, 0.0);
		return;
		case 4:
		draw_change_color(0.0, 1.0, 0.0);
		return;
		case 5:
		draw_change_color(1.0, 0.0, 0.0);
		return;
		case 6:
		draw_change_color(0.0, 1.0, 1.0);
		return;
	}
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

int read_int(FILE* fp)
{
	int ret = 0;
	char c = fgetc(fp);
	while (c != '\n')
	{
		ret = ret*10 + c - 48;

		c = fgetc(fp);
	}

	return ret;
}

void get_high_scores()
{
	char fn[] = "saves/hs-~-~~~-~~~";
	printf("%d, %d, %d\n", gamemode, width, height);
	fn[9]   = gamemode + 48;

	fn[11]  = width/100 + 48;
	fn[12]  = (width%100)/10 + 48;
	fn[13]  = width%10 + 48;

	fn[15]  = height/100 + 48;
	fn[16]  = (height%100)/10 + 48;
	fn[17]  = height%10 + 48;
	FILE* fp = fopen(fn, "r");
	if (!fp && gamemode == 1)
	{
		high_score[0] = 500000;
		high_score[1] = 400000;
		high_score[2] = 300000;
		high_score[3] = 200000;
		high_score[4] = 100000;
		high_score[5] = 0;
		return;
	}
	else if (!fp && gamemode == 2)
	{
		high_score[0] = 0;
		high_score[1] = 220000;
		high_score[2] = 320000;
		high_score[3] = 420000;
		high_score[4] = 520000;
		high_score[5] = 620000;
		return;
	}
	if (gamemode == 1)
	{
		high_score[0] = read_int(fp);
		high_score[1] = read_int(fp);
		high_score[2] = read_int(fp);
		high_score[3] = read_int(fp);
		high_score[4] = read_int(fp);
		high_score[5] = 0;
	}
	if (gamemode == 2)
	{
		high_score[0] = 0;
		high_score[1] = read_int(fp);
		high_score[2] = read_int(fp);
		high_score[3] = read_int(fp);
		high_score[4] = read_int(fp);
		high_score[5] = read_int(fp);
	}

	/* 
	printf("Score 1.: %d\n", high_score[0]);
	printf("Score 2.: %d\n", high_score[1]);
	printf("Score 3.: %d\n", high_score[2]);
	printf("Score 4.: %d\n", high_score[3]);
	printf("Score 5.: %d\n", high_score[4]);
	/* */

	fclose(fp);
}

void save_high_scores()
{
	char fn[] = "saves/hs-~-~~~-~~~";
	fn[9]   = gamemode + 48;

	fn[11]  = width/100 + 48;
	fn[12]  = (width%100)/10 + 48;
	fn[13]  = width%10 + 48;

	fn[15]  = height/100 + 48;
	fn[16]  = (height%100)/10 + 48;
	fn[17]  = height%10 + 48;
	//printf("TEST: %s\n", fn);
	FILE* fp = fopen(fn, "w");
	fprintf(fp, "%d\n", high_score[0]);
	fprintf(fp, "%d\n", high_score[1]);
	fprintf(fp, "%d\n", high_score[2]);
	fprintf(fp, "%d\n", high_score[3]);
	fprintf(fp, "%d\n", high_score[4]);
	fclose(fp);
}

void increase_score(int a)
{
	switch (gamemode)
	{
		case 1:
		high_score[score_loc] += a;

		while (score_loc > 0 && high_score[score_loc - 1] < high_score[score_loc])
		{
			int tmp = high_score[score_loc - 1];
			high_score[score_loc - 1] = high_score[score_loc];
			high_score[score_loc] = tmp;

			score_loc--;
		}
		break;

		case 2:
		high_score[score_loc] = a;

		while (score_loc < 6 && high_score[score_loc + 1] < high_score[score_loc])
		{
			int tmp = high_score[score_loc + 1];
			high_score[score_loc + 1] = high_score[score_loc];
			high_score[score_loc] = tmp;

			score_loc++;
		}
		break;
	}

}

