/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/23 11:12:56 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//executes the cmd with its argiments after checking of its existence and its permissions
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

// takes the cmd line and execute or turns an error if it counter one
void execution(t_data *data, int length, char ***env)
{
	int	i;
	int	id;
	int	**pipes;
	t_data	*tmp;

	if (length == 1 && check_builtins(data, 1, env) == 0) // check if there is no pipes and the cmd is a builtin so it executes it on the parent process
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
				if (tmp->in_files != NULL)
					open_infiles(tmp);
				if (tmp->out_files != NULL)
					open_outfiles(tmp);
			}
			check_builtins(tmp, 0, env);
			execute_cmd(tmp, *env);
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
