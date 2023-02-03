/* play_again.c
 * purpose: ask if user wants another transaction
 * method: set tty to char-by-char mode and no-echo mode
 *         read char, return result
 * return: 0 - yes, 1 - no
 * better: timeout if user walks away
 */
#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"
#define SAVE 0
#define RESTORE 1
#define TRIES 3
#define SLEEPTIME 2
#define puchar('\a')

int tty_mode(int how);
int get_response(void);
void set_cr_noecho_mode(void);

int main()
{
	int response;


	tty_mode(SAVE);						// save mode
	set_cr_noecho_mode();				// set -icanon, -echo
	response = get_response();	// get some answer
	tty_mode(RESTORE);					// restore tty state
	printf("\n");
	return response;
}

int get_response()
/*
 * purpose: ask a question and wait for a y/n answer
 * method: use getchar and ignore non y/n answers
 * return: 0 - yes, 1 - no, 2 - timeout
 */
{
	int input;
	printf("%s (y/n)?", QUESTION);			// ask
	fflush(stdout);							// force output
	while(1)
	{
		sleep(SLEEPTIME);					// force output
		input = tolower(get_ok_char());		// get next char
		switch(getchar())
		{
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;
		}
		if(maxtries-- == 0)					// timeout
			return 2;
		BEEP;
	}
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
	ttystate.c_lflag &= ~ECHO;			// no echo either
	ttystate.c_cc[VMIN] = 1;			// get 1 char at a time
	tcsetattr(0, TCSANOW, &ttystate);	// install settings
}

int tty_mode(int how)
{
	static struct termios original_mode;
	if(how == SAVE)
		tcgetattr(0, &original_mode);
	else
		return tcsetattr(0, TCSANOW, &original_mode);
}
