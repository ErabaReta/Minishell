/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/04 20:33:57 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cmd(t_data *data,  char **env)
{
	char	*full_cmd;
	// char	**args;
	
	// args = ft_split(data->cmd, ' '); // split the cmd to have it with its args
	if (char_in_cmd(data->args[0], '/') != -1)// if the cmd include '/'  in it then execute it
	{
		full_cmd = check_relative_path(data->args[0]);
	}
	else 
	{
		full_cmd = check_paths(env, data->args[0]);
	}
	if (full_cmd == NULL)
	{
		//TODO free if there is somtihn to free (probably not)
		exit(1);
	}


	// printf("full cmd is -> %s\n", full_cmd);
	
	execve(full_cmd, data->args, env);
}
void	open_infiles(t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (data->in_files[i] != NULL)
	{
		if (access(data->in_files[i], F_OK) == 0)
		{
			if (access(data->in_files[i], R_OK) == 0)
			{
				i++;
			}
			else
			{
				printf("Minishell: permission denied: %s\n", data->in_files[i]);
				exiter(data, 1);
			}
		}
		else
		{
			printf("Minishell: %s: No such file or directory\n", data->in_files[i]);
			exiter(data, 1);
		}
	}
	fd = open(data->in_files[i - 1], O_RDONLY);// TODO open the last infile not the first one and protect failing
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", data->in_files[i - 1]);//TODO custume ERR here
		exiter(data, 1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	open_outfiles(t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (data->out_files[i] != NULL)
	{
		if (access(data->out_files[i], F_OK) == 0)
		{
			if (access(data->out_files[i], W_OK) == 0)
			{
				fd = open(data->out_files[i], O_WRONLY | O_TRUNC);// TODO open the last infile not the first one and protect failing
				if (fd < 0)
				{
					printf("minishell: %s: No such file or directory\n", data->out_files[i]);//TODO custume ERR here
					exiter(data, 1);
				}
				i++;
			}
			else
			{
				printf("Minishell: permission denied: %s\n", data->out_files[i]);
				exiter(data, 1);
			}
		}
		else
		{
				fd = open(data->out_files[i], O_WRONLY | O_TRUNC | O_CREAT);// TODO open the last infile not the first one and protect failing
				if (fd < 0)
				{
					printf("minishell: %s: No such file or directory\n", data->out_files[i]);//TODO custume ERR here
					exiter(data, 1);
				}
				i++;
		}
		if (data->out_files[i] != NULL)
			close(fd);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

// closing all the not needed pipes and redirect the needed ones
void	piping(t_data *data, int **pipes, int length, int i)
{
	int j = 0;

	while (j < length - 1) // closing all the not needed pipes
	{
		if (j != i ) 
		{
			close(pipes[j][PIPE_INPUT]);
			// printf("closing the input of pipe %d in child %d\n", j, i);
		}
		if ( j != i - 1)
		{
			close(pipes[j][PIPE_OUTPUT]);
			// printf("closing the output of pipe %d in child %d\n", j, i);
		}
		j++;
	}
	if (i != 0) // change the input to be the output of cmd before exept if this is the not first cmd
	{
			
			// fprintf(stderr, "cmd => \"%s\"data->in_files[0] %s", data->cmd, data->in_files[0]);
		// if (data->in_files[0] != NULL)
		// {
		// 	open_infiles(data);
		// }
		// else
			dup2(pipes[i - 1][PIPE_OUTPUT], STDIN_FILENO);
		close(pipes[i - 1][PIPE_OUTPUT]);
				// printf("changing the standard input of child %d to be ouput of pipe %d then close it\n", i, i - 1);
	}
	if (i != length - 1) // chande the output to be the input of the next cmd exept if this is not the last cmd
	{
		// if (data->out_files[0] != NULL)
		// 	open_outfiles(data);
		// else
			dup2(pipes[i][PIPE_INPUT], STDOUT_FILENO);
		close(pipes[i][PIPE_INPUT]);
	}
	if (data->in_files[0] != NULL)
		open_infiles(data);
	if (data->out_files[0] != NULL)
		open_outfiles(data);
}

void execution(t_data *data, int length, char **env)
{
	int	i;
	int	id;
	int	**pipes;
	t_data	*tmp;

	if (length == 1 && check_builtins(data, 1) == 0)
	{
		return ;
	}
	if (length >= 2) // if there is no '|' in the cmd there is no need to create pipe
		pipes = (int **)malloc(sizeof(int *) * (length - 1));
	i = 0;
	while (i < length - 1) // allocating needed pipes and open them all (we will close the ones we dont need later)
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
	/*
	 *	creating child prossesse for each cmd then executing the cmd within it,
	 *	also if there pipes '|' changing the output for the cmd to be the input for the next cmd.
	 */
	while (i < length && tmp != NULL)
	{
		id = fork();// creating process
		if (id == -1) // check if prossess created
		{
			printf("error : cant create process %d\n", i);
		}
		if (id == 0) // if we are in the child proccess do this :
		{
			// printf("cmd => \"%s\"\n", tmp->args[0]);
			if (length >= 2)
			{
				// fprintf(stderr, "infile1=>%s, cmd=>%s\n", tmp->in_files[0], tmp->cmd);
				piping(tmp, pipes, length, i);
			}
			else
			{

				if (tmp->in_files[0] != NULL)
				{
					open_infiles(tmp);
				}
				if (tmp->out_files[0] != NULL)
					open_outfiles(tmp);
			}
			check_builtins(tmp, 0);
			execute_cmd(tmp, env);
		}
		tmp = tmp->next;
		i++;
	}
	//=
	int j = 0;
	while (j < length - 1)// for the parent prosses I close all the pipe I created before
	{
			close(pipes[j][PIPE_OUTPUT]);
			close(pipes[j][PIPE_INPUT]);
		j++;
	}
	i = 0;
	while (i < length) // wait for all the CMDs to be done the continue to give the prompt later
	{
		wait(NULL);
		i++;
	}
}
