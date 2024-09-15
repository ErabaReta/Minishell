/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:25:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 20:22:23 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *cmd)
{
	if ((ft_strncmp(cmd, "pwd", 4) == 0)
		|| (ft_strncmp(cmd, "env", 4) == 0)
		|| (ft_strncmp(cmd, "exit", 5) == 0)
		|| (ft_strncmp(cmd, "cd", 3) == 0)
		|| (ft_strncmp(cmd, "echo", 5) == 0)
		|| (ft_strncmp(cmd, "unset", 6) == 0)
		|| (ft_strncmp(cmd, "export", 7) == 0))
		return (1);
	return (0);
}

void	run_builtin(t_data *data, int is_parent)
{
	int	files_status;

	files_status = 0;
	if (data->files != NULL && is_parent)
		files_status = handle_files(data->files, is_parent);
	if (files_status != 0)
		get_specials()->exit_status = 1;
	else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
		get_specials()->exit_status = ft_pwd();
	else if (ft_strncmp(data->args[0], "env", 4) == 0)
		get_specials()->exit_status = ft_env(env_list_to_table(), is_parent);
	else if (ft_strncmp(data->args[0], "exit", 5) == 0)
		ft_exit(data, is_parent, &(get_specials()->exit_status));
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
		get_specials()->exit_status = ft_cd(data);
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
		get_specials()->exit_status = ft_echo(data);
	else if (ft_strncmp(data->args[0], "unset", 6) == 0)
		get_specials()->exit_status = ft_unset(data);
	else if (ft_strncmp(data->args[0], "export", 7) == 0)
		ft_export(data, &(get_specials()->exit_status));
}

int	check_builtins(t_data *data, int is_parent)
{
	int	fd[2];
	int	files_status;

	fd[0] = safer_dup(STDIN_FILENO);
	fd[1] = safer_dup(STDOUT_FILENO);
	files_status = 0;
	if ((data->args == NULL || *(data->args) == NULL))
	{
		if (data->files != NULL && is_parent)
			get_specials()->exit_status = handle_files(data->files, is_parent);
		safer_dup2(fd[0], STDIN_FILENO);
		safer_dup2(fd[1], STDOUT_FILENO);
		return (0);
	}
	if (is_builtin(data->args[0]))
		run_builtin(data, is_parent);
	else
		return (-1);
	if (!is_parent)
		exiter(get_specials()->exit_status);
	safer_dup2(fd[0], STDIN_FILENO);
	safer_dup2(fd[1], STDOUT_FILENO);
	return (0);
}
