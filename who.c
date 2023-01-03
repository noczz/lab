/* who.c - who with buffered reads
 *       - surpresses empty records
 *       - formats time nicely
 *       - buffers input(using utmplib)
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>	// ctime
#include <utmp.h>	// struct utmp

#define SHOWHOST	// include remote machine on output

void show_info(struct utmp *pcurrent_record);

int          utmp_open(char * filename);
struct utmp* utmp_next();
int          utmp_reload();
void         utmp_close();

int main()
{
	struct utmp *putbuf;					// read info into here
	int utmpfd;								// read from this discriptor

	if(utmp_open(UTMP_FILE) == -1)
	{
		perror(UTMP_FILE);					// UTMP_FILE is the pathname of utmp file
		exit(1);
	}

	while((putbuf = utmp_next()) != (struct utmp *)NULL)
		show_info(putbuf);
	utmp_close(putbuf);
	return 0;
}

void show_info(struct utmp *pcurrent_record)
{
	time_t timet=pcurrent_record->ut_tv.tv_sec;
//	if(pcurrent_record->ut_type != USER_PROCESS) return;
	printf("%-8.8s ", pcurrent_record->ut_user);		// the logname
	printf("%-8.8s ", pcurrent_record->ut_line);		// device name of tty - "/dev/"
	printf("%12.12s ", ctime(&timet)+4);				// login time
#ifdef SHOWHOST
	printf("(%s)", pcurrent_record->ut_host);			// the host
#endif
	printf("\n");										// newline
}
