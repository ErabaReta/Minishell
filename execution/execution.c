/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/06/05 17:27:01 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *check_paths(char *cmd, char **env)
{
	int	i;
	char **paths;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
		{
			if (access(cmd, F_OK) == 0)
			{
				if (access( cmd , X_OK) == 0)
					return (ft_strdup(cmd));
				else
				{
					printf("minishell: permission denied: %s\n", cmd);
					return (NULL);
				}
			}
			printf("minishell: command not found: %s\n", cmd);
			return (NULL);
		}
		i++;
	}

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=",  5) == 0)
		{
			break ;
		}
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	// if ((env[5]) != '\0')
	
	paths = ft_split(env[i] + 5, ':');
	// for(int k = 0; paths[k] != NULL; k++)
	// {
	// 	printf("%s\n",  paths[k]);
	// }
	i = 0;
	while (paths[i] != NULL)
	{
		paths[i] = ft_strjoin(paths[i], "/");
		// printf("checking if %s exist ..\n", ft_strjoin(paths[i], cmd));//
		if (access(ft_strjoin(paths[i], cmd), F_OK) == 0)
		{
			// printf("the file exist ==> %s\n", ft_strjoin(paths[i], cmd));//
			if(access(ft_strjoin(paths[i], cmd), X_OK) == 0)
			{
				// printf("the file executable ==> %s\n", ft_strjoin(paths[i], cmd));//
				return (ft_strjoin(paths[i], cmd));
			}
			else
			{
				printf("minishell: permission denied: %s\n", cmd);
				return (NULL);
			}
		}
		// printf("NO\n");//
		i++;
	}
	printf("minishell: command not found: %s\n", cmd);
	return (NULL);
}

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
			char *path = check_paths(args[0], env);//
			if (path == NULL)
			{
				int j = 0;
				while (j < length - 1)
				{
						close(pipes[j][PIPE_INPUT]);
						close(pipes[j][PIPE_OUTPUT]);
					j++;
				}
				exit(0);
			}
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
			execve(path, args, env);
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
