/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 01:18:31 by eouhrich         ###   ########.fr       */
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
		exiter(2);
	}
	if (ft_strncmp(data->args[0] , "..", 3) == 0 || ft_strncmp(data->args[0] , "", 1) == 0)
	{
		print_err(data->args[0]);
		print_err(": command not found\n");
		exiter(127);
	}
	if (char_in_cmd(data->args[0], '/') != -1)// if the cmd include '/'  in it then execute it
		full_cmd = check_relative_path(data->args[0]);
	else 
		full_cmd = check_paths(data->args[0]);
	if (execve(full_cmd, data->args, env_list_to_table()) == -1)
	{
		perror("minishell: ");
		exiter(127);
	}
	exiter(get_specials()->exit_status);
}

void	sighandler_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		printf("quit (core dumped)\n");
	}
}

void	sig_exit_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
}


void	close_unwanted(int a_pipe[2], int length, int *i, int *fd_out)
{
	if (*i != length - 1) 
		close(a_pipe[PIPE_INPUT]);//
	if (*i != 0)
		close (*fd_out);
	*fd_out = a_pipe[PIPE_OUTPUT];//
	*i += 1;
}

void	childs_factory(t_data *tmp, int length, int *child_pids)
{
	int	fd_out;
	int	a_pipe[2];
	int	i;

	i = 0;
	while (i < length && tmp != NULL)
	{
		if (length >= 2 && i != length - 1)
			pipe(a_pipe);
		child_pids[i] = fork();// creating process
		if (child_pids[i] == -1) // check if prossess created
		{
			perror("minishell ");
			exiter(1);
		}
		if (child_pids[i] == 0) // if we are in the child proccess do this :
		{
			if (piping(a_pipe, length, i, fd_out) && tmp->files != NULL)
					handle_files(tmp->files, 0);
			if (check_builtins(tmp, 0) != 0)
				execute_cmd(tmp);
		}
		close_unwanted(a_pipe, length, &i, &fd_out);
		tmp = tmp->next;
	}
}

// takes the cmd line and execute or turns an error if it counter one
void execution(t_data *data, int length)
{
	int	i;
	t_spec	*svars;
	int status;
	
	svars = get_specials();
	if (length == 1 && check_builtins(data, 1) == 0) // check if there is no pipes and the cmd is a builtin so it executes it on the parent process
		return ;
	int *child_pids = (int *)mallocate(sizeof(int) * (length));
	childs_factory(data, length, child_pids);
	i = 0;
	status = 0;
	while (i < length) // wait for all the CMDs to be done the continue to give the prompt later
	{
		// wait(NULL);
		svars->child_p = waitpid(child_pids[i], &status, 0);
		i++;
	}
	svars->exit_status = ((status >> 8) & 255);
}
