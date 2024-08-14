/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:25:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/14 20:37:16 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// checks is the cmd is builtin than execute it
int	check_builtins(t_data *data, int is_parent)
{
	int	fd[2];
	t_spec *svars = get_specials();
	int	files_status = 0;

	fd[0] = dup(STDIN_FILENO);// keeps the standerd inputs in case of redirecting it
	fd[1] = dup(STDOUT_FILENO);// keeps the standerd outputs in case of redirecting it
	
	if (data->args == NULL || *(data->args) == NULL)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (ft_strncmp(data->args[0], "pwd", 4) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
		{
			ft_pwd();
			svars->exit_status = 0;
		}
		else
			svars->exit_status = 1;
	}
	else if (ft_strncmp(data->args[0], "env", 4) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
		{
			ft_env(env_list_to_table());
			svars->exit_status = 0;
		}
		else
			svars->exit_status = 1;
	}
	else if (ft_strncmp(data->args[0], "exit", 5) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
		{
			if(is_parent)
				print_err("exit\n");
			close(fd[0]);
			close(fd[1]);
			exiter(svars->exit_status);
		}
		else
			svars->exit_status = 1;
	}
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
		{
			svars->exit_status = ft_cd(data);
		}
		else
			svars->exit_status = 1;
	}
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
		{
			ft_echo(data);
			svars->exit_status = 0;
		}
		else
			svars->exit_status = 1;
	}
	else if (ft_strncmp(data->args[0], "unset", 6) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
		{
			ft_unset(data);
			svars->exit_status = 0;
		}
			svars->exit_status = 1;
	}
	else if (ft_strncmp(data->args[0], "export", 7) == 0)
	{
		if (is_parent && data->in_files != NULL)
			files_status = open_infiles(data);
		if (is_parent && data->out_files != NULL && files_status == 0)
			files_status = open_outfiles(data);
		if (files_status == 0)
			ft_export(data, &(svars->exit_status));
		else
			svars->exit_status = 1;
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	if (!is_parent)
	{
		close(fd[0]);
		close(fd[1]);
		exiter(svars->exit_status);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
