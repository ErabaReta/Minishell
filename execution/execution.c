/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:56 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/16 14:33:37 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_shlvl(int length)
{
	if (length < 2)
		return ;
	if (env_search("SHLVL") != NULL
		&& ft_atoi(env_search("SHLVL")->value) - 1 >= 1000)
	{
		print_3_err("minishell: warning: shell level (",
			ft_itoa(ft_atoi(env_search("SHLVL")->value) - 1, 0),
			") too high, resetting to 1\n", -1);
		free(env_search("SHLVL")->value);
		env_search("SHLVL")->value = ft_itoa(1, 1);
	}
}

void	execute_cmd(t_data *data, int length)
{
	char	*full_cmd;

	if (ft_strncmp(data->args[0], "..", 3) == 0
		|| ft_strncmp(data->args[0], ".", 2) == 0
		|| ft_strncmp(data->args[0], "", 1) == 0)
		print_3_err(data->args[0], ": command not found\n", NULL, 127);
	if (char_in_cmd(data->args[0], '/') != -1)
		full_cmd = check_relative_path(data->args[0]);
	else
		full_cmd = check_paths(data->args[0]);
	handle_shlvl(length);
	if (execve(full_cmd, data->args, env_list_to_table()) == -1)
	{
		perror("minishell: ");
		exiter(127);
	}
	exiter(get_specials()->exit_status);
}

void	close_unwanted(int a_pipe[2], int length, int *i, int *fd_out)
{
	if (*i != length - 1)
		ft_close(a_pipe[PIPE_INPUT]);
	if (*i != 0)
		ft_close(*fd_out);
	*fd_out = a_pipe[PIPE_OUTPUT];
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
			safer_pipe(a_pipe);
		child_pids[i] = safer_fork();
		if (child_pids[i] == 0)
		{
			if (piping(a_pipe, length, i, fd_out) && tmp->files != NULL)
				handle_files(tmp->files, 0);
			if (check_builtins(tmp, 0) != 0)
				execute_cmd(tmp, length);
			exiter(get_specials()->exit_status);
		}
		close_unwanted(a_pipe, length, &i, &fd_out);
		tmp = tmp->next;
	}
}

void	execution(t_data *data, int length)
{
	int		i;
	int		status;
	int		*child_pids;

	if (length == 1 && check_builtins(data, 1) == 0)
		return ;
	child_pids = (int *)mallocate(sizeof(int) * (length));
	if (ft_strncmp("./minishell", data->args[0], ft_strlen(data->args[0])))
		setup_signal_handler(1, SIG_IGN, sighandler_exev);
	else
		setup_signal_handler(1, SIG_IGN, SIG_IGN);
	get_specials()->exit_status = 0;
	childs_factory(data, length, child_pids);
	i = 0;
	status = 0;
	while (i < length)
	{
		get_specials()->child_p = waitpid(child_pids[i], &status, 0);
		i++;
	}
	if ((((status & 127) + 1) >> 1) > 0)
		get_specials()->exit_status = (status & 127) + 128;
	else
		get_specials()->exit_status = ((status >> 8) & 255);
}
