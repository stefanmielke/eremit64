/*
  Eremit v 1.0 Made by Andreas Henningsson
  Date: Thu Mar 18 2004
  THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY! USE AT YOUR OWN RISK!
  Send bug reports to <andreas.henningsson@telia.com>
*/
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "board.h"

#include <libdragon.h>
#define printf debugf

SDL_Surface *screen;
SDL_Surface *bg;
SDL_Surface *ball;
SDL_Surface *brick;
SDL_Surface *selection;

int main() {
	SDL_Event event;
	int done = 0;

	printf("Welcome to Eremit\nInitialize SDL...\n");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		abort();
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Unable to set 640x480 video: %s\n", SDL_GetError());
		abort();
	}
	SDL_WM_SetCaption("Eremit - Andreas Henningsson", "Eremit");

	// load the gfx
	printf("Load graphics...\n");
	brick = IMG_Load("gfx/brick.tga");
	ball = IMG_Load("gfx/ball.tga");
	selection = IMG_Load("gfx/selection.tga");
	bg = IMG_Load("gfx/bg.tga");

	printf("Initialize board...\n");
	Board *board[81];
	initBoard(board);

	printf("Initialize sound...\n");
	printf("Start game...\n");
	while (!done) {
		// events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					done = 1;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						int brickPos = getBrick(board, event.motion.x, event.motion.y);
						if (isSelected(board))
							moveTwo(board, brickPos);
						else
							moveOne(board, brickPos);
					}
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)  // quit
						done = 1;

					if (event.key.keysym.sym == SDLK_SPACE)	 // reset the game on space
					{
						initBoard(board);
					}
					break;
			}
		}

		drawBoard(screen, bg, ball, brick, selection, board);

		SDL_Flip(screen);
		SDL_Delay(10);
	}
}
