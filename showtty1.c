/* showtty.c
 * display some current tty settings
 */

#include <stdio.h>
#include <termios.h>

typedef struct flaginfo {
	int fl_value;
	char *fl_name;
} flaginfo;

int showbaud( int thespeed );
int show_some_flags( struct termios *ptty );
int show_flagset( int thevalue, flaginfo thebitnames[] );

flaginfo input_flags[] = {
	IGNBRK,	"Ignore break condition",
	BRKINT,	"Signal interrupt on break",
	IGNPAR,	"Ignore char with pariry errors",
	PARMRK,	"Mark parity errors",
	INPCK,	"Enable input parity check",
	ISTRIP,	"Strip character",
	INLCR,	"Map NL to CR on input",
	IGNCR,	"Ignore CR",
	ICRNL,	"Map CR to NL on input",
	IXON,	"Enable start/stop output control",
//	_IXANY,	"Enable any char to restart ouput",
	IXOFF,	"Enable start/stop input control",
	0,		NULL
};

flaginfo local_flags[] = {
	ISIG,	"Enable signals",
	ICANON,	"Canonical input (erase and kill)",
//	_XCASE,	"Canonical upper/lower appearance",
	ECHO,	"Enable echo",
	ECHOE,	"Echo ERASE as BS-SPACE-BS",
	ECHOK,	"Echo KILL by starting new line",
	0,		NULL
};

int main(void)
{
	struct termios ttyinfo;
	if( tcgetattr( 0, &ttyinfo ) == -1 ){				// this struct holds ttyp info
		perror( "cannot get params about stdin" );		// get info
		return(1);
	}
														// show info
	showbaud( cfgetospeed( &ttyinfo ) );				// get + show baud rate
	printf( "The erase character is ascii %d, Ctrl-%c\n", ttyinfo.c_cc[VERASE], ttyinfo.c_cc[VERASE]-1 + 'A' );
	printf( "The line kill character is ascii %d, Ctrl-%c\n", ttyinfo.c_cc[VKILL], ttyinfo.c_cc[VKILL]-1 + 'A' );
	show_some_flags( &ttyinfo );

	return 0;
}

int showbaud( int thespeed )
/*
 * prints the speed in english
 */
{
	printf( "the baud rate is " );
	switch ( thespeed ){
		case B300 : printf( "300 \n" ); break;
		case B600 : printf( "600 \n" ); break;
		case B1200: printf( "1200\n" ); break;
		case B1800: printf( "1800\n" ); break;
		case B2400: printf( "2400\n" ); break;
		case B4800: printf( "4800\n" ); break;
		case B9600: printf( "9600\n" ); break;
		default: printf( "Fast\n" ); break;
	}
}


int show_some_flags( struct termios *ptty )
/*
 * show the values of two of the flag sets_: c_iflag and c_lflag
 * adding c_oflag and c_cflag is pretty routine - just add new
 * tables above and a bit more code below.
 */
{
	show_flagset(ptty->c_iflag, input_flags);
	show_flagset(ptty->c_lflag, local_flags);
}

int show_flagset( int thevalue, flaginfo thebitnames[] )
{
	int i;
	for ( i=0; thebitnames[i].fl_value; i++ )
	{
		printf(" %s is ", thebitnames[i].fl_name);
		if( thevalue & thebitnames[i].fl_value )
			printf("ON\n");
		else
			printf("OFF\n");
	}
}
