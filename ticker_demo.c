/* ticker_demo.c
 * demonstrates use of interval timer to generate regular
 * signals, which are in turn caught and used to count down
 */

#include <stdio.h>
#include <stdlib.h>			// stdlib()
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

int main(void)
{
	void countdown(int signum);
	int set_ticker(int n_msecs);

	signal(SIGALRM, countdown);
	if(set_ticker(500) == -1)
		perror("set_ticker");
	else
		while(1)
			pause();
	return 0;
}

void countdown(int signum)
{
	static int num = 10;
	printf("%d..", num--);
	fflush(stdout);
	if(num < 0)
	{
		printf("DONE! \n");
		exit(0);
	}
}

int set_ticker(int n_msecs)
/* [from set_ticker.c]
 * set_ticker(number_of_milliseconds)
 * arranges for interval timer to issue SIGALRMs at regular intervals
 * return -1 on error, 0 for ok
 * arg in milliseconds, converted into whole seconds and microseconds
 * note: set_ticker(0) turn off ticker
 */
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;					// int part
	n_usecs = (n_msecs % 1000) * 1000L;		// remainder

	new_timeset.it_interval.tv_sec = n_sec;		// set reload
	new_timeset.it_interval.tv_usec = n_usecs;	// set ticker value

	new_timeset.it_value.tv_sec = 3;		// store this
	new_timeset.it_value.tv_usec = 300 * 1000L;		// store this

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
