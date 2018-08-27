CC     = gcc
OUTDIR = bin
INDIR  = src

minesweeper: 
	mkdir -p bin
	$(CC) $(INDIR)/minesweeper.c -o $(OUTDIR)/minesweeper -lncurses
sudoku:
	mkdir -p bin
	$(CC) $(INDIR)/sudoku.c -o $(OUTDIR)/sudoku -lncurses
tetris:
	mkdir -p bin
	$(CC) $(INDIR)/tetris.c -o $(OUTDIR)/tetris -lncurses
snake:
	mkdir -p bin
	$(CC) $(INDIR)/snake.c -o $(OUTDIR)/snake -lncurses

all: minesweeper sudoku tetris snake

clean:
	rm -rf $(OUTDIR)
