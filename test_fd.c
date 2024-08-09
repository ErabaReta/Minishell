#include "minishell.h"

int main()
{
	int fd[2];
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);




	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);


	close(fd[0]);
	close(fd[1]);

	printf("hi\n");
}