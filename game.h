#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <string>

#include "solution.h"
#include "gamescreen.h"
#include "game.h"

class GameScreen;

class Game {
	public:
		Game(int, int);
		~Game();

		Solution* solution;
		GameScreen* gameScreen;

		bool initialised;

		void GenerateClues();
		
		std::vector<std::vector<int> > Row_Clues;
		std::vector<std::vector<int> > Column_Clues;
	
		int game_X;
		int game_Y;
		
		int VerifySolution();	
	private:	
		void Rows();
		void Cols();
};

#endif
