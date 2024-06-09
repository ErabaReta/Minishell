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

void execute_cmd()
{
	
}

void execution(t_data *data, int length, char **env)
{
	int	i;
	int	id;
	int	**pipes;
	t_data	*tmp;

	if (length >= 2)
		pipes = (int **)malloc(sizeof(int *) * (length - 1));
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

	while (i < length && tmp != NULL)
	{
		id = fork();
		// pipes = (int *)malloc(sizeof(int) * 2);
		// if (pipe(pipes) == -1)
		// {
		// 		printf("error : cant create pipe %d\n", i + 1);
		// }
		if (id == -1)
		{
				printf("error : cant create process %d\n", i + 1);
		}
		if (id == 0)
		{
			char	**args = ft_split(tmp->cmd, ' ');
			if (length >= 2)
			{
				int j = 0;
				while (j < length - 1)
				{
					if (j != i )
					{
						close(pipes[j][PIPE_INPUT]);
					}
					if ( j != i - 1)
					{
						close(pipes[j][PIPE_OUTPUT]);
					}
					j++;
				}
				//=
				// if (i == 0)
				// 	{
				// 	close(pipes[i][PIPE_OUTPUT]);

				// 	}
				// else
				// {
					if (i != 0)
					{

						dup2(pipes[i - 1][PIPE_OUTPUT], STDIN_FILENO);
					close(pipes[i - 1][PIPE_OUTPUT]);
					}
				// }
				// if (i == length - 1)
				// 	close(pipes[i - 1][PIPE_INPUT]);
				// else
				// {
					if (i != length - 1)
					{

						dup2(pipes[i][PIPE_INPUT], STDOUT_FILENO);
					close(pipes[i][PIPE_INPUT]);
					}
				// }
			}
			execve(args[0], args, env);
		}
		// else
		// {
		// 	if (length >= 2 )
		// 	{
		// 		close(pipes[PIPE_INPUT]);
		// 	}
		// }
		tmp = tmp->next;
		i++;
	}
	//=
	int j = 0;
	while (j < length - 1)
	{
			close(pipes[j][PIPE_OUTPUT]);
			close(pipes[j][PIPE_INPUT]);
		j++;
	}
	i = 0;
	
	while (i < length)
	{
		wait(NULL);
		i++;
	}
	exit (0);
}
