CC     = gcc
OUTDIR = bin
INDIR  = src

minesweeper: 
	$(CC) $(INDIR)/minesweeper.c -o $(OUTDIR)/minesweeper -lncurses
sudoku:
	$(CC) $(INDIR)/sudoku.c -o $(OUTDIR)/sudoku -lncurses
tetris:
	$(CC) $(INDIR)/tetris.c -o $(OUTDIR)/tetris -lncurses
snake:
	$(CC) $(INDIR)/snake.c -o $(OUTDIR)/snake -lncurses

all: minesweeper sudoku tetris snake

clean:
	rm $(OUTDIR)/snake
	rm $(OUTDIR)/tetris
	rm $(OUTDIR)/sudoku
	rm $(OUTDIR)/minesweeper
