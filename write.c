/* write.c
 *
 * purpose: send messages to another terminal
 * method: open the other terminal for output then
 * copy from stdin to that terminal
 * shows: a terminal is just a file supporting regular i/o
 * usage: write ttyname
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// write()
#include <unistd.h>

// open()
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
	int fd;
	char buf[BUFSIZ];
	// check args
	if(argc != 2)
	{
		fprintf(stderr, "usage: write ttyname\n");
		exit(1);
	}
	// open devices
	fd = open(argv[1], O_WRONLY);
	if(fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	// loop until EOF on input
	while(fgets(buf, BUFSIZ, stdin) != NULL)
		if(write(fd, buf, strlen(buf)) == -1)
			break;
	close(fd);
	return 0;
}
