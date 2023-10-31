#ifndef __GAMESCREEN_H_INCLUDED__
#define __GAMESCREEN_H_INCLUDED__

#include "game.h"
#include "navigation.h"

class Game;
class Navigation;

class GameScreen {
	public:
		GameScreen(Game*);
		~GameScreen();
		
		Game* game;
		Navigation* nav;

		void Update();
		
		std::vector<std::vector<int> > userMatrix;
		int totalWidth;
		int totalHeight;

		int GetMaxWidth();
		int GetMaxHeight();
	
		int GetRowWidth(int);
		
		int maxWidth;
		int maxHeight;

		int bufferZone;
	private:
		//
};

#endif
