#include "navigation.h"
#include "gamescreen.h"

#include "curses.h"
#include <vector>

Navigation::Navigation(int init_x, int init_y, GameScreen* init_gs, Game* init_g) {
	width = init_x;
	height = init_y;
	
	g = init_gs;
	game = init_g;

	leftBoundary = 5 + init_gs->maxWidth; //maxwidth i.e. . . . |   <-
	rightBoundary = 3 + init_gs->maxWidth + width; 	 //totalwidth
	bottomBoundary = init_gs->GetMaxHeight() + init_g->solution->solutionData.size();	 //starting pos + height + maxnocluesvertical + 1
	topBoundary = init_gs->GetMaxHeight() + 1;		 // starting pos

	cursor_X = 0;
	cursor_Y = 0;

	xPos = leftBoundary;
	yPos = topBoundary;
}

Navigation::~Navigation() {

}

int Navigation::processInput() {
	char c = getch();

	switch (c) {
	case 65:
		yPos -= 1;
		cursor_Y -= 1; break;
	case 66:
		yPos += 1;
		cursor_Y += 1; break;
	case 67:
		xPos += 2;
		cursor_X += 1; break;
	case 68:
		xPos -= 2;
		cursor_X -= 1; break;
	}

	//process arrow key
	if (xPos < leftBoundary) {
		xPos = leftBoundary;
	}
	if (xPos > rightBoundary) {
		xPos = rightBoundary;
	}
	if (yPos < topBoundary) {
		yPos = topBoundary;
	}
	if (yPos > bottomBoundary) {
		yPos = bottomBoundary;
	}
	
	//cursor thing
	if (cursor_X < 0) {
		cursor_X = 0;
	}
	
	if (cursor_X > (width / 2 ) - 1) {
		cursor_X = (width / 2) - 1;
	}

	if(cursor_Y < 0) {
		cursor_Y = 0;
	}
	
	if(cursor_Y > (height / 2) - 1) {
		cursor_Y = (height / 2) - 1;
	}
	
	//process x and y pos of solution modifier
	
	switch(c) {
		case 'q':
			return 1;
		case 'x':
			g->userMatrix[cursor_Y][cursor_X] = 2;
			return 0;
		case 'c':
			g->userMatrix[cursor_Y][cursor_X] = 1;
			return 0;
		case 'z':
			g->userMatrix[cursor_Y][cursor_X] = 0;
			return 0;
		case 32: //ENTER
			int t = game->VerifySolution();
			return t;
	}
	return 0;
}

