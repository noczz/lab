/* animation.c
 * purpose: bounce a message back and forth across the screen
 * complie: gcc animation.c -lncurses -o animation.c
 */
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define LEFTEDGE 10
#define RIGHTEDGE COLS-10
#define ROW 10

int main(int argc, char** argv)
{
	char message[] = "jennia";
	char blank[]   = "      ";
	int dir = 1;
	int pos = LEFTEDGE;

	initscr();
	clear();
	while(1)
	{
		move(ROW, pos);
		addstr(message);		// draw string
		move(LINES-1, COLS-1);	// park the curses
		refresh();
		sleep(1);
		move(ROW, pos);			// erase string
		addstr(blank);
		pos += dir;
		if(pos >= RIGHTEDGE)
			dir = -1;
		if(pos <= LEFTEDGE)
			dir = +1;
	}
	return 0;
}
