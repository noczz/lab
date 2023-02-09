#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <unistd.h>

typedef struct point {
	int x;
	int y;
} point;

int F_TopHaf(int x);
int F_BotHaf(int x);
int FlipLines(int y);
int Origin(point *pp_, point p, int lines, int cols);


int main(int argc, char **argv)
{
	point p;
	point p_;

	initscr();

	clear();

	// The top half of the heart
	// draw the x from 0 to positive infinity
	p.x=0;
	while(1)
	{
		p.y=FlipLines(F_TopHaf(p.x));
		Origin(&p_, p, LINES/2, COLS/2);

		if(!(0<=p_.y&&p_.y<LINES && 0<=p_.x&&p_.x<COLS))
			break;

//		sleep(1);
		move(p_.y, p_.x);
		addch('#');
		refresh();

		p.x++;
	}

	// draw the x from 0 to negative infinity
	p.x=0;
	while(1)
	{
		p.y=FlipLines(F_TopHaf(p.x));
		Origin(&p_, p, LINES/2, COLS/2);

		if(!(0<=p_.y&&p_.y<LINES && 0<=p_.x&&p_.x<COLS))
			break;

//		sleep(1);
		move(p_.y, p_.x);
		addch('#');
		refresh();

		p.x--;
	}

	// The bottom half of the heart
	// draw the x from 0 to positive infinity
	p.x=0;
	while(1)
	{
		p.y=FlipLines(F_BotHaf(p.x));
		Origin(&p_, p, LINES/2, COLS/2);

		if(!(0<=p_.y&&p_.y<LINES && 0<=p_.x&&p_.x<COLS))
			break;

//		sleep(1);
		move(p_.y, p_.x);
		addch('#');
		refresh();

		p.x++;
	}

	// draw the x from 0 to negative infinity
	p.x=0;
	while(1)
	{
		p.y=FlipLines(F_BotHaf(p.x));
		Origin(&p_, p, LINES/2, COLS/2);

		if(!(0<=p_.y&&p_.y<LINES && 0<=p_.x&&p_.x<COLS))
			break;

//		sleep(1);
		move(p_.y, p_.x);
		addch('#');
		refresh();

		p.x--;
	}

	move(LINES-1, 0);
	getch();

	endwin();
	return 0;
}

int F_TopHaf(int x)
{
	int y=0;
	double x_ = fabs(x*(0.02));	// x scope
	y = (int)
	(
		(10)				// y scope
		*
		(
			pow(x_, 2.0/3.0)
			+
			pow
			(
				pow(x_, 4.0/3.0)
				-
				4*pow(x_, 2.0)
				+
				4
				,
				0.5
			)
		)
	);


	// debug
//	move(0, 0);
//	printw("(%d, %d)\n", x, y);

	return y;
}

int F_BotHaf(int x)
{
	int y=0;
	double x_ = fabs(x*(0.02));	// x scope
	y = (int)
	(
		(10)				// y scope
		*
		(
			pow(x_, 2.0/3.0)
			-
			pow
			(
				pow(x_, 4.0/3.0)
				-
				4*pow(x_, 2.0)
				+
				4
				,
				0.5
			)
		)
	);


	// debug
//	move(0, 0);
//	printw("(%d, %d)\n", x, y);

	return y;
}

int FlipLines(int y)
{
	return LINES-1-y;
}

int Origin(point *pp_, point p, int lines, int cols)
{
	pp_->y=p.y-lines;
	pp_->x=p.x+cols;
	return 0;
}
