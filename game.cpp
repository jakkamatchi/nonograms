#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "game.h"
#include "solution.h"
#include "gamescreen.h"

Game::Game(int x_t, int y_t) {
	solution = new Solution(x_t, y_t);

	game_X = x_t;
	game_Y = y_t;

	GenerateClues();

	initialised = true;

	gameScreen = new GameScreen(this);
}

Game::~Game() {

}

void Game::GenerateClues() {
	int count = 0;
	std::vector<int> tempRow;
	
	Cols();
	Rows();
}

void Game::Rows() {
	int count = 0;
	std::vector<int> tempRow;
		
	for (int i = 0; i < game_Y; i++) {
		for (int j = 0; j < game_X; j++) {
			if (solution->solutionData[i][j] == 0) {
				if (count > 0) {
					tempRow.push_back(count);
				}

				count = 0;
			}
			else if (solution->solutionData[i][j] == 1) {
				count++;
			}	
		}
		if (count != 0) {	
			tempRow.push_back(count);
		}
		if (tempRow.size() == 0) {
			tempRow.push_back(0);
		}


		Row_Clues.push_back(tempRow);

		tempRow.resize(0);
		count = 0;
	}	
}


void Game::Cols() {
	int count = 0;
	std::vector<int> tempCol;
		
	int max = 0;

	for (int i = 0; i < game_X; i++) {
		for (int j = 0; j < game_Y; j++) {
			if (solution->solutionData[j][i] == 0) {
				if (count > 0) {
					tempCol.push_back(count);
				}

				count = 0;
			}
			else if (solution->solutionData[j][i] == 1) {
				count++;
			}	
		}
		if (count != 0) {	
			tempCol.push_back(count);
		}
		if (tempCol.size() == 0) {
			tempCol.push_back(0);
		}
		
		int temp = tempCol.size();
		if(temp > max) {
			max = temp;
		}

		count = 0;
		Column_Clues.push_back(tempCol);
		tempCol.resize(0);
	}

	for (int i = 0; i < Column_Clues.size(); i++) {
		int temp = max - Column_Clues[i].size();
		
		for (int j = 0; j < temp; j++) {
			Column_Clues[i].push_back(-1);
		}
	}
}

int Game::VerifySolution() {
	int a;
	int b;

	for (int i = 0; i < solution->solutionData.size(); i++) {
		for (int j = 0; j < solution->solutionData[0].size(); j++) {
			a = solution->solutionData[i][j];
			b = gameScreen->userMatrix[i][j];
			
		       	if (b == 2) {
				b = 0;
			}	
			
			if (b != a ) {
				//failure
				return 2;
			}
		}
	}

	//success
	return 3;
}
