#include "minishell.h"
#include <string.h>
#include <stdio.h>
int main(int ac, char **av)
{
	int fd1[2];
	int fd2[2];
	if (pipe(fd1) == -1)
	{
		printf("could not create pipe\n");
		return 1;
	}
	if (pipe(fd2) == -1)
	{
		printf("could not create pipe\n");
		return 1;
	}
	int id = fork();
	if (id == -1)
	{
		printf("could not create process\n");
		return 1;
	}
	if (id != 0)
	{
		// close(fd[0]);
		int nbr = atoi(av[1]);
		write(fd1[1], &nbr, sizeof(nbr));
		// sleep(1);
		read(fd2[0], &nbr, sizeof(nbr));
		printf("the parent resieved the number %d\n", nbr);

	}
	if (id == 0)
	{
		// close(fd[1]);
		int x;
		read(fd1[0], &x, sizeof(x));
		printf("the child resieved the number %d\n", x);
		x *= 10;
		write(fd2[1], &x, sizeof(x));
	}
	return 0;
}