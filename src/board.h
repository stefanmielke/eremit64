/*
  Eremit v 1.0 Made by Andreas Henningsson
  Date: Thu Mar 18 2004
  THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY! USE AT YOUR OWN RISK!
  Send bug reports to <andreas.henningsson@telia.com>
*/

#include <SDL/SDL.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define HEIGHT 50
#define WIDTH 50

#define NORTH 18
#define SOUTH 18
#define EAST 2
#define WEST 2

typedef struct {
	int brick;
	int ball;
	int selected;
} Board;

int getBrick(Board *[], int, int);

void initBoard(Board *[]);

void drawBoard(SDL_Surface *, SDL_Surface *, SDL_Surface *, SDL_Surface *, SDL_Surface *,
			   Board *[]);

int isSelected(Board *[]);

void deSelectAll(Board *[]);

void moveOne(Board *[], int);

void moveTwo(Board *[], int);

int moveOk(Board *[]);

void doMove(Board *[]);
