/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/13 06:22:36 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//executes the cmd with its argiments after checking of its existence and its permissions
void execute_cmd(t_data *data)
{
	char	*full_cmd;
	// char	**args;

	if (ft_strncmp(data->args[0] , ".", 2) == 0)
	{
		print_err("minishell: .: filename argument required\n");
		exiter(NULL, 2);
	}
	if (ft_strncmp(data->args[0] , "..", 3) == 0)
	{
		print_err("..: command not found\n");
		exiter(NULL, 127);
	}
	// args = ft_split(data->cmd, ' '); // split the cmd to have it with its args
	if (char_in_cmd(data->args[0], '/') != -1)// if the cmd include '/'  in it then execute it
	{
		full_cmd = check_relative_path(data->args[0]);
	}
	else 
	{
		full_cmd = check_paths(data->args[0]);
	}
	if (full_cmd == NULL)
	{
		exiter(data, 1);
	}


	// printf("full cmd is -> %s\n", full_cmd);
	
	execve(full_cmd, data->args, env_list_to_table());
}

void	sighandler_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		printf("quit (core dumped)\n");
	}
	exit (0);
}

void	sig_exit_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
}

// takes the cmd line and execute or turns an error if it counter one
void execution(t_data *data, int length)
{
	int	i;
	// int	id;
	int	**pipes;
	t_data	*tmp;

	if (length == 1 && check_builtins(data, 1) == 0) // check if there is no pipes and the cmd is a builtin so it executes it on the parent process
	{
		return ;
	}
	if (length >= 2) // if there is no '|' in the cmd there is no need to create pipe
		pipes = (int **)mallocate(sizeof(int *) * (length - 1));
	i = 0;
	while (i < length - 1) // allocating needed pipes and open them all (we will close the ones we dont need later)
	{
		pipes[i] = (int *)mallocate(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			// printf("error : cant create pipe %d\n", i + 1);
			print_err("minishell: cannot open a pipe\n");
			exiter(NULL, 1);
		}
		i++;
	}

	i = 0;
	
	tmp = data;
	/*
	 *	creating child prossesse for each cmd then executing the cmd within it,
	 *	also if there pipes '|' changing the output for the cmd to be the input for the next cmd.
	 */
	
	int *child_pids = (int *)mallocate(sizeof(int) * (length));
	while (i < length && tmp != NULL)
	{
		child_pids[i] = fork();// creating process
		if (child_pids[i] == -1) // check if prossess created
		{
			// printf("error : cant create process %d\n", i);
			print_err("minishell: cant create process\n");
			exiter(NULL, 1);
		}
		if (child_pids[i] == 0) // if we are in the child proccess do this :
		{
			// setup_signal_handler(0, sighandler_exev, sighandler_exev);
			// printf("cmd => \"%s\"\n", tmp->args[0]);
			if (length >= 2)
			{
				// fprintf(stderr, "infile1=>%s, cmd=>%s\n", tmp->in_files[0], tmp->cmd);
				piping(tmp, pipes, length, i);
			}
			else
			{
					// printf("it is here tmp->in_files=>%p || tmp->out_files=>%p\n",tmp->in_files, tmp->out_files);

				if (tmp->in_files != NULL)
					open_infiles(tmp);
				if (tmp->out_files != NULL)
				{
					open_outfiles(tmp);
				}
			}
			if (tmp->args != NULL && *(tmp->args) != NULL)
			{
				check_builtins(tmp, 0);
				execute_cmd(tmp);
			}
			exiter(tmp, 1);
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
	int status;
	while (i < length) // wait for all the CMDs to be done the continue to give the prompt later
	{
		// wait(NULL);
		setup_signal_handler(1, SIG_DFL, SIG_IGN);
		waitpid(child_pids[i], &status, 0);
		//execve return 0 if successed or -1 if failed we must hundle manualy -1 it must be 127
		printf("status = %d\n", WEXITSTATUS(status));
		i++;
	}
	// t_spec *svars = get_specials();
	// svars->exit_status = 5;//((status >> 8) & 255);
}
