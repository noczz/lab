/* sleep.c
 * purpose	show how sleep works
 * usage	./sleep
 * outline	sets handler, set alarm, pauses, then returns
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
//#define SHHHH

int main(void)
{
	void wakeup(int signum);
	printf("about to sleep for 3 seconds\n");
	signal(SIGALRM, wakeup);		// catch it
	alarm(3);						// set clock
	pause();						// freeze here
	printf("Morning so soon?\n");	// back to work
	return 0;
}

void wakeup(int signum)
{
#ifndef SHHHH
	printf("Alarm received from kernel\n");
#endif
}
