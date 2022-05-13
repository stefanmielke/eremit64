/*
  Eremit v 1.0 Made by Andreas Henningsson
  Date: Thu Mar 18 2004
  THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY! USE AT YOUR OWN RISK!
  Send bug reports to <andreas.henningsson@telia.com>
*/
#include "board.h"

static int pos1;
static int pos2;

/*
 * return the direction of the move
 */
int getDirection() {
	int dir = 0;
	switch (pos1 - pos2) {
		case 2:
			dir = 16;
			break;
		case -2:
			dir = 1;
			break;
		case -18:
			dir = 4;
			break;
		case 18:
			dir = 64;
			break;
	}
	return dir;
}

/*
 * move the ball from pos1 to pos2
 */
void doMove(Board *board[]) {
	int direction = getDirection();

	// remove the first ball
	board[pos1]->ball = FALSE;

	// add ball to the empty brick
	board[pos2]->ball = TRUE;

	// remove ball in between
	switch (direction) {
		case 1:
			board[pos1 + 1]->ball = FALSE;
			break;
		case 4:
			board[pos1 + 9]->ball = FALSE;
			break;
		case 16:
			board[pos1 - 1]->ball = FALSE;
			break;
		case 64:
			board[pos1 - 9]->ball = FALSE;
			break;
	}
}

/*
 * Check if the move is ok
 */
int moveOk(Board *board[]) {
	/* statement true if move is == 2 squares long */
	if (pos1 - WEST == pos2 || pos1 + EAST == pos2 || pos1 - NORTH == pos2 ||
		pos1 + SOUTH == pos2) {
		/* do user move over a ball? */
		int dir = getDirection();
		switch (dir) {
			case 1:
				dir = pos1 + 1;
				break;
			case 16:
				dir = pos1 - 1;
				break;
			case 4:
				dir = pos1 + 9;
				break;
			case 64:
				dir = pos1 - 9;
				break;
		}
		/* statement true if user move over a ball */
		if (board[dir]->ball == TRUE)
			return TRUE;
		else
			return FALSE;
	} else
		return FALSE;
}

/*
 * move one should contains a ball, else reset the move
 */
void moveOne(Board *board[], int brick) {
	if (board[brick]->ball == TRUE) {
		board[brick]->selected = TRUE;
		pos1 = brick;
	} else
		deSelectAll(board);
}

/*
 * move to should NOT contain a ball, else reset the move
 */
void moveTwo(Board *board[], int brick) {
	if (board[brick]->ball == FALSE) {
		board[brick]->selected = TRUE;
		pos2 = brick;

		if (moveOk(board))
			doMove(board);
	}
	deSelectAll(board);
}

/*
 * Check if any brick is selected
 */
int isSelected(Board *board[]) {
	int i;
	for (i = 0; i < 81; i++) {
		if (board[i]->selected == TRUE)
			return TRUE;
	}
	return FALSE;
}

/*
 * Remove all selections
 */
void deSelectAll(Board *board[]) {
	int i;
	for (i = 0; i < 81; i++) {
		board[i]->selected = FALSE;
	}
}

static int between(int tal, int intS) {
	if (tal > intS && tal < intS + WIDTH)
		return TRUE;
	else
		return FALSE;
}

int getBrick(Board *board[], int x, int y) {
	int bx, by;
	int pos = 0;

	for (by = 0; by < 9; by++)	// loop height
	{
		for (bx = 0; bx < 9; bx++)	// loop width
		{
			if (between(x, bx * WIDTH) == TRUE &&  // check pos
				between(y, by * HEIGHT) == TRUE) {
				return pos;	 // return it if found
			}
			pos++;
		}
	}
	return 0;
}

/*
 * Draw the board
 */
void drawBoard(SDL_Surface *screen, SDL_Surface *bg, SDL_Surface *ball, SDL_Surface *brick,
			   SDL_Surface *selection, Board *board[]) {
	int x, y;
	int pos = 0;
	SDL_Rect dest;

	dest.x = 0;
	dest.y = 0;
	dest.w = 450;
	dest.h = 450;

	SDL_BlitSurface(bg, NULL, screen, &dest);

	for (y = 0; y < 9; y++) {
		for (x = 0; x < 9; x++) {
			dest.x = x * WIDTH;
			dest.y = y * HEIGHT;
			dest.w = WIDTH;
			dest.h = HEIGHT;

			if (board[pos]->brick == 1)
				SDL_BlitSurface(brick, NULL, screen, &dest);

			if (board[pos]->selected == 1)
				SDL_BlitSurface(selection, NULL, screen, &dest);

			if (board[pos]->ball == 1)
				SDL_BlitSurface(ball, NULL, screen, &dest);

			pos++;
		}
	}
}

/*
 * Init the board
 */
void initBoard(Board *board[]) {
	int i;
	int pos = 0;
	for (i = 0; i < 81; i++) {
		board[pos] = (Board *)malloc(sizeof(Board));
		board[pos]->brick = 1;
		board[pos]->ball = 1;
		board[pos]->selected = 0;
		pos++;
	}

	// is there a better way to do this?
	board[0]->brick = 0;
	board[0]->ball = 0;	 // line 1
	board[1]->brick = 0;
	board[1]->ball = 0;
	board[2]->brick = 0;
	board[2]->ball = 0;
	board[6]->brick = 0;
	board[6]->ball = 0;
	board[7]->brick = 0;
	board[7]->ball = 0;
	board[8]->brick = 0;
	board[8]->ball = 0;

	board[9]->brick = 0;
	board[9]->ball = 0;	 // line 2
	board[10]->brick = 0;
	board[10]->ball = 0;
	board[11]->brick = 0;
	board[11]->ball = 0;
	board[15]->brick = 0;
	board[15]->ball = 0;
	board[16]->brick = 0;
	board[16]->ball = 0;
	board[17]->brick = 0;
	board[17]->ball = 0;

	board[18]->brick = 0;
	board[18]->ball = 0;  // line 3
	board[19]->brick = 0;
	board[19]->ball = 0;
	board[25]->brick = 0;
	board[25]->ball = 0;
	board[26]->brick = 0;
	board[26]->ball = 0;

	board[54]->brick = 0;
	board[54]->ball = 0;  // line 4
	board[55]->brick = 0;
	board[55]->ball = 0;
	board[61]->brick = 0;
	board[61]->ball = 0;
	board[62]->brick = 0;
	board[62]->ball = 0;

	board[63]->brick = 0;
	board[63]->ball = 0;  // line 5
	board[64]->brick = 0;
	board[64]->ball = 0;
	board[65]->brick = 0;
	board[65]->ball = 0;
	board[69]->brick = 0;
	board[69]->ball = 0;
	board[70]->brick = 0;
	board[70]->ball = 0;
	board[71]->brick = 0;
	board[71]->ball = 0;

	board[72]->brick = 0;
	board[72]->ball = 0;  // line 6
	board[73]->brick = 0;
	board[73]->ball = 0;
	board[74]->brick = 0;
	board[74]->ball = 0;
	board[78]->brick = 0;
	board[78]->ball = 0;
	board[79]->brick = 0;
	board[79]->ball = 0;
	board[80]->brick = 0;
	board[80]->ball = 0;

	board[40]->ball = 0;  // center
}
