/* hello1.c
 * purpose show the minimal calls needed to use curses
 * outline initialize, draw stuff, wait for input, quit
 */

#include <stdio.h>
#include <curses.h>

void main(void)
{
	initscr();					// turn on curses
								// send requests

	clear();					// clear screen
	move(10, 10);				// row 10, col 120
	addstr("Hello, world");		// add a string
	move(LINES-1, 0);			// move to last line
	refresh();					// update the screen
	getch();					// wait for user input
	endwin();					// turn off curses
}
