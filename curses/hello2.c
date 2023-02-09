/* hello2.c
 * purpose show how to use fuctions with a loop
 * outline initialize, draw stuff, wrap up
 */
#include <stdio.h>
#include <ncurses.h>

int main(void)
{
	int i;

	initscr();			// turn on curses
	clear();			// draw some stuff
	for(i=0; i<LINES; i++)
	{
		move(i, i);
		if(i%2 == 1)
			standout();
		addstr("Hello, world\n!");
		if(i%2 == 1)
			standend();
	}
	refresh();			// update the screen
	getchar();			// wait for user input
	endwin();			// reset the tty etc
}
