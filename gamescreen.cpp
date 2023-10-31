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
			if (nav->cursor_X == j) {
				attron(COLOR_PAIR(1));
			}

			if(game->Column_Clues[j][i] != -1) {
				printw("%d", game->Column_Clues[j][i]);
				attroff(COLOR_PAIR(1));
				printw(" ");
			}
			else {
				attroff(COLOR_PAIR(1));
				printw("  ");
			}

			attroff(COLOR_PAIR(1));
		}
		printw("\n");
	}



	for (int i = 0; i < totalWidth; i++) {
		if (nav->leftBoundary + (nav->cursor_X * 2)== i) {
			attron(COLOR_PAIR(1));
			printw("-");
			attroff(COLOR_PAIR(1));
		}
		else {
			printw("-");
		}
	}

	printw("\n");
	
	for (int j = 0; j < game->Row_Clues.size(); j++) {
		if (nav->cursor_Y == j) {
			attron(COLOR_PAIR(1));

		}
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
			bool col = 0;

			if(nav->cursor_X == i || nav->cursor_Y == j) {
				attron(COLOR_PAIR(1));
				col = true;
			}

			if (ipt == 0) {
				printw(" ");
			}
			else if (ipt == 1) {
				printw("X");
			}
			else if (ipt == 2) {
				printw("-");
			}
			
			if(nav->cursor_X != i || nav->cursor_Y == j) {
				printw(" ");
				attroff(COLOR_PAIR(1));
			}
			else {
				attroff(COLOR_PAIR(1));	
				printw(" ");
			}
		}

		attroff(COLOR_PAIR(1));

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
