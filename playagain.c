/* play_again.c
 * purpose: ask if user wants another transaction
 * method: set tty to char-by-char mode and no-echo mode
 *         read char, return result
 * return: 0 - yes, 1 - no, 2 - timeout
 * better: reset terminal mode on Interrupt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define QUESTION "Do you want another transaction"
#define SAVE 0
#define RESTORE 1
#define SLEEPTIME 5
#define TRIES 3 
#define BEEP putchar('\a')

int tty_mode(int how);
int get_response(void);
void set_cr_noecho_mode(void);
char get_ok_char(void);
void set_nodelay_mode(void);
void ctrl_c_handler(int signum);

int main()
{
	int response;


	tty_mode(SAVE);						// save mode
	set_cr_noecho_mode();				// set -icanon, -echo
	set_nodelay_mode();
	signal(SIGINT, ctrl_c_handler);		// handle INT
	signal(SIGQUIT, SIG_IGN);			// ignore QUIT
	response = get_response();			// get some answer
	tty_mode(RESTORE);					// restore tty state
	printf("%d\n", response);
	return response;
}

int get_response(void)
/*
 * purpose: ask a question and wait for a y/n answer
 * method: use getchar and ignore non y/n answers
 * return: 0 - yes, 1 - no, 2 - timeout
 */
{
	int input;
	int maxtries = TRIES;
	printf("%s (y/n)?", QUESTION);			// ask
	fflush(stdout);							// force output
	while(1)
	{
		sleep(SLEEPTIME);					// wait a bit
		input = tolower(get_ok_char());		// get next char
		switch(input)
		{
			case 'y': return 0;
			case 'n': return 1;
		}
		if(maxtries-- == 0)					// timeout
			return 2;
		BEEP;
	}
}

char get_ok_char(void)
/*
 * skip over non - legal chars and return y,Y,n,N or EOF
 */
{
	int c;
	while((c = getchar()) != EOF && strchr("yYnN", c) == NULL);
	return c;
}

void set_cr_noecho_mode(void)
	/*
 * purpose: put file descriptor 0 into char-by-char mode and noecho mode
 * method: use bits in termios
 */
{
	struct termios ttystate;
	tcgetattr(0, &ttystate);			// read current setting
	ttystate.c_lflag &= ~ICANON;		// no buffering
//	ttystate.c_lflag &= ~ECHO;			// no echo either
	ttystate.c_cc[VMIN] = 1;			// get 1 char at a time
	tcsetattr(0, TCSANOW, &ttystate);	// install settings
}

void set_nodelay_mode(void)
/*
 * purpose: put file descriptor 0 into no-delay mode
 * method: use fcntl to set bits
 * notes: tcsetattr() will do something similar, but it is complicated
 */
{
	int termflags;
	termflags = fcntl(0, F_GETFL);		// read current settings
	termflags |= O_NONBLOCK;				// flip on nodelay bit
	fcntl(0, F_SETFL, termflags);		// and install them
}

int tty_mode(int how)
{
	static struct termios original_mode;
	if(how == SAVE)
		tcgetattr(0, &original_mode);
	else
		return tcsetattr(0, TCSANOW, &original_mode);
}

void ctrl_c_handler(int signum)
{
	tty_mode(RESTORE);
	printf("\n%d", __LINE__);
	exit(1);
}
