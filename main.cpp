#include <iostream>
#include <vector>

#include <time.h>
#include <stdlib.h>
#include <curses.h>

#include "game.h"
#include "consts.h"
#include "gamescreen.h"
#include "navigation.h"

//TO DO:

//Diplay a grid with current game status
//parse input to determine player input
//modify board state

int main (int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: "<< argv[0] << " <int x_dim> <int y_dim>";
		return 1;
	}
	
	int x_dim;
	int y_dim;

	try {
		x_dim = std::stoi(argv[1], nullptr, 10);
		y_dim = std::stoi(argv[2], nullptr, 10);
	}	
	catch (...) {
		std::cerr << x_dim << " " << y_dim << std::endl;
		std::cerr << "Invalid Input: Please enter two integer values";
		return 1;
	}	
	
	if (x_dim == 0 || y_dim == 0) {
		std::cerr << "Invalid Input: Integers must be non-zero";
		return 1;
	}
	
	initscr();
	cbreak();
	noecho();

	Game g(x_dim, y_dim);
	int state = 0;

	while (state == 0) {
		clear();
		g.gameScreen->Update();
		move(g.gameScreen->nav->yPos, g.gameScreen->nav->xPos);
	
		refresh();

		state = g.gameScreen->nav->processInput();
		//refresh();

		if (state == 2) {		
			//wrong solution, keep playing
			move(g.gameScreen->nav->bottomBoundary + 2, 0);
			printw("Incorrect !\nPress any key to keep playing !\n");
			getch();

			state = 0;
		}
		else if (state == 3) {
			move(g.gameScreen->nav->bottomBoundary + 2, 0);
		}
	}
	
	if(state == 3) {	
		
		printw("Success !\nPress any key to quit !\n");
		getch();
	}

	endwin();

	return 0;
}
