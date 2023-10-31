#ifndef __NAVIGATION_H_INCLUDED__
#define __NAVIGATION_H_INCLUDED__

#include "gamescreen.h"
#include "curses.h"

class GameScreen;
class Game;

class Navigation {
	public:
		Navigation(int, int, GameScreen*, Game*);
		~Navigation();

		Game* game;	
		GameScreen* g;

		int xPos;
		int yPos;
	
		int cursor_X;
		int cursor_Y;

		int width;
		int height;

		int leftBoundary;
		int rightBoundary;
		int topBoundary;
		int bottomBoundary;

		int processInput();
	private:
		//
};

#endif
