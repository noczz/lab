#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>		// write
#include <fcntl.h>		// creat

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *s1, char *s2);

int main(int argc, char *argv[])
{
	int in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];

													// check args
	if(argc != 3)
	{
		fprintf(stderr, "%s [SYNOPSIS ERROR] pleas use: $cp {source} {destination}\n", *argv);
		exit(1);
	}

													// open files
	if((in_fd = open(argv[1], O_RDONLY)) == -1)
		oops("Cannot open ", argv[1]);
	if((out_fd = creat(argv[2], O_RDONLY)) == -1)
		oops("Cannot open ", argv[2]);

													// copy files
	while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if(write(out_fd, buf, n_chars) != n_chars)
			oops("Write error to ", argv[2]);

	if(n_chars == -1)
		oops("Read error from ", argv[1]);

													// close files
	if(close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");

	return 0;
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s", s1);
	perror(s2);
	exit(1);
}
