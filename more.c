#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *fp);
int see_more(FILE *fp_tty);

int main(int argc, char *argv[])
{
	FILE *fp;
	if ( argc == 1 )
		do_more(stdin);
	else
	{
		while(--argc)
		if((fp = fopen(*++argv, "r")) != NULL)
		{
			do_more(fp);
			fclose(fp);
		} else
		{
			exit(1);
		}
	}
	return 0;
}

void do_more(FILE *fp)
/*
 * read PAGELEN lines, then call see_more() for further instructions
 */
{
	char line[LINELEN];
	int num_of_lines = 0;
	int reply;
	FILE *fp_tty;
	if(!(fp_tty = fopen("/dev/tty", "r"))) exit(1);
	while(fgets(line, LINELEN, fp))		// more input
	{
		if(num_of_lines == PAGELEN)		// full screen?
		{
			reply = see_more(fp_tty);	// y: ask user
			if(!reply) break;			// n: done
			num_of_lines -= reply;
		}
		if(fputs(line, stdout) == EOF)
			exit(1);
		num_of_lines++;
	}
}

int see_more(FILE *fp_tty)
/*
 * Print message, wait for response, return # of lines to advance
 * q means no, space means yes, CR means one line.
 */
{
	int c;
	printf("\033[7m more? \033[m");		// reverse on a vt100
	while((c = getc(fp_tty)) != EOF)		// get response
	{
		if(c == 'q')	return 0;		// q         -> N
		if(c == ' ')	return PAGELEN;	// space     => next page
		if(c == '\n')	return 1;		// Enter key => 1 line
	}
	return 0;
}
