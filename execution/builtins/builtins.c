/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:25:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/14 12:51:53 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// checks is the cmd is builtin than execute it
int	check_builtins(t_data *data, int is_parent)
{
	int	fd[2];
	t_spec *svars = get_specials();

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
		// fprintf(stderr, "it is the cmd pwd\n");///////////
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_pwd();
		svars->exit_status = 0;
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "env", 4) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_env(env_list_to_table());
		svars->exit_status = 0;
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "exit", 5) == 0)
	{
		if(is_parent)
			printf("exit");
		close(fd[0]);
		close(fd[1]);
		exiter(svars->exit_status);
	}
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		svars->exit_status = ft_cd(data);
	}
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_echo(data);
		svars->exit_status = 0;
	}
	else if (ft_strncmp(data->args[0], "unset", 6) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_unset(data);
		svars->exit_status = 0;
	}
	else if (ft_strncmp(data->args[0], "export", 7) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_export(data, &(svars->exit_status));
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
