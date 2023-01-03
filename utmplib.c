/* utmplib.c - function to buffer reads from utmp file
 *
 *		funcntions are
 *		utmp_open(filename) - openfile
 *			return -1 on error
 *		utmp_next()			- return pointer to next struct
 *			return NULL on eof
 *		utmp_close()		- close file
 *
 *		reads NRECS per read and then doles them out from the buffer
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>			// open()
#include <sys/types.h>
#include <utmp.h>			// utmp
#include <unistd.h>			// read()

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

int          utmp_open(char * filename);
struct utmp* utmp_next();
int          utmp_reload();
void         utmp_close();

static char utmpbuf[NRECS*UTSIZE];			// storage
static int num_recs;						// num stored
static int cur_rec;							// next to go
static int fd_utmp = -1;					// read from

int utmp_open(char * filename)
{
	fd_utmp = open(filename, O_RDONLY);		// open it
	cur_rec = num_recs = 0;					// no recs yet
	return fd_utmp;							// report
}

struct utmp *utmp_next()
{
	struct utmp *prec;
	if(fd_utmp == -1)								// error
		return NULLUT;
	if(cur_rec == num_recs && utmp_reload() == 0)	// any more?
	/*
	 * if cur_rec not equal to num_recs,
	 * utmp_reload() would not be call.
	 */
		return NULLUT;
													// get address of next record
	prec = (struct utmp *) &utmpbuf[cur_rec*UTSIZE];
	cur_rec++;
	return prec;
}

int utmp_reload()
/*
 * read next bunch of records into buffer
 */
{
	int amt_read;										// read them in
	amt_read = read(fd_utmp, utmpbuf, NRECS*UTSIZE);	// how many did we get?
	num_recs = amt_read/UTSIZE;							// reset pointer
	cur_rec = 0;
	return num_recs;
}

void utmp_close()
{
	if(fd_utmp != -1)									// don't close if not
		close(fd_utmp);									// open
}
