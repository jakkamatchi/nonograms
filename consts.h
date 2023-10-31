#ifndef __CONSTS_H_INCLUDED__
#define __CONSTS_H_INCLUDED__

#include <curses.h>

void Splash() {
	printw("NONOGRAMS FOR TERMINAL\n");

	printw("|-------------------------------------|\n");
	printw("| | | |-| | | |-| /-\\ /-\\ |-| /|\\ /-- |\n");
	printw("| |\\| | | |\\| | | | - |-/ |-| ||| \\-\\ |\n");
	printw("| | | |_| | | |_| |_| |\\  | | ||| --/ |\n");
	printw("|-------------------------------------|\n");

	//char* compilation = "Compiled: " + __DATE__ + " " + __TIME__ + "\n";

	//printw(compilation);
	printw("Jack Lecerf\n");

	return;
}

#endif
