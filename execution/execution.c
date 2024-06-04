/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/06/04 16:23:54 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
void execute_cmd()
{
	
}

void execution(t_data *data, int length, char **env)
{
	int	i;
	int	id;
	int	**pipes;
	t_data	*tmp;
	
	pipes = (int **)malloc(sizeof(int *));
	i = 0;
	while (i < length - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
				printf("error : cant create pipe %d\n", i + 1);
		}
		i++;
	}

	i = 0;
	tmp = data;
	while (i < length)
	{
		id = fork();
		if (id == -1)
		{
				printf("error : cant create process %d\n", i + 1);
		}
		if (id == 0)
		{
			char	**args = ft_split(tmp->cmd, ' ');
			if (i == 0)
				close(pipes[i][0]);
			else
				dup2(pipes[i][0], STDIN_FILENO);
			if (i == length - 1)
				close(pipes[i][1]);
			else
				dup2(pipes[i][1], STDOUT_FILENO);
			execve(args[0], args, env);
		}
		else
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < length)
	{
		wait(NULL);
	}
	exit (0);
}
