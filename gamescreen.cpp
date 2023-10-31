#include "gamescreen.h"
#include "game.h"

#include <iostream>
#include <iomanip>
#include <vector>

#include <curses.h>

GameScreen::GameScreen(Game* g) {
	game = g;
	
	maxWidth = GetMaxWidth();
	maxHeight = GetMaxHeight();

	bufferZone = 5;
	
	totalWidth = bufferZone + maxWidth;

	userMatrix.resize(game->solution->solutionData.size());

	for (int i = 0; i < userMatrix.size(); i++) {
		userMatrix[i].resize(game->solution->solutionData[i].size());
		for (int j = 0; j < userMatrix[i].size(); j++) {
			userMatrix[i][j] = 0;
		}
	}

	userMatrix[userMatrix.size() - 1][userMatrix[0].size() - 1] = 1;
	nav = new Navigation((2 * userMatrix[0].size()), (2 * userMatrix.size()), this, g);
}

GameScreen::~GameScreen() {
	//
}

void GameScreen::Update() {
	totalWidth = maxWidth + 4 + (2 * game->game_X);
	int progress = GetMaxHeight();
	std::string s = "";

	for (int i = 0; i < progress; i++) {
		for (int c = 0; c < maxWidth + 2; c++) {
			printw(" "); 
		}

		printw(" | ");
		for (int j = 0; j < game->Column_Clues.size(); j++) {
			if(game->Column_Clues[j][i] != -1) {
				printw("%d ", game->Column_Clues[j][i]);
			}
			else {
				printw("  ");
			}
		}
		printw("\n");
	}



	for (int i = 0; i < totalWidth; i++) {
		printw("-");
	}

	printw("\n");
	
	for (int j = 0; j < game->Row_Clues.size(); j++) {
		for (int i = 0; i < game->Row_Clues[j].size(); i++) {
			printw("%d ", game->Row_Clues[j][i]);

			int dif = maxWidth -  GetRowWidth(j);
		}

		for (int h = 0; h < maxWidth - GetRowWidth(j); h++) {
			printw(" ");
		}

		printw("  | ");
		
		for (int i = 0; i < userMatrix[j].size(); i++) {
			int ipt = userMatrix[j][i];

			if (ipt == 0) {
				printw("  ");
			}
			else if (ipt == 1) {
				printw("X ");
			}
			else if (ipt == 2) {
				printw("- ");
			}
		}

		printw("\n");
	}

	printw("\n");
}

int GameScreen::GetRowWidth(int id) {
	std::string s = "";
	int currentCount = 0;
	
	int numberOfSpaces = game->Row_Clues[id].size() - 1;

	for (int i = 0; i < game->Row_Clues[id].size(); i++) {
		s = game->Row_Clues[id][i];
		currentCount = currentCount + s.size();
	}
	
	return currentCount + numberOfSpaces;
}

int GameScreen::GetMaxWidth() {
	int max = 0;
	int currentCount = 0;
	int numberOfSpaces = 0;
	std::string s = "";

	for (int i = 0; i < game->Row_Clues.size(); i++) {
		numberOfSpaces = game->Row_Clues[i].size() - 1;

		for (int j = 0; j < game->Row_Clues[i].size(); j++) {
			s = game->Row_Clues[i][j];
			currentCount = currentCount + s.size();
		}
		currentCount = currentCount + numberOfSpaces;
	
		if (currentCount > max) {
			max = currentCount;
		}
		
		currentCount = 0;
		s.resize(0);
		numberOfSpaces = 0;
	}
	
	return max;
}

int GameScreen::GetMaxHeight() {
	int max = 0;
	int currentCount = 0;

	for (int i = 0; i < game->Column_Clues.size(); i++) {
		currentCount = game->Column_Clues[i].size();

		if (currentCount > max) {
			max = currentCount;
		}

		currentCount = 0;
	}
	
	return max;
}
