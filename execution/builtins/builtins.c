/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:25:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/08 22:05:18 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// checks is the cmd is builtin than execute it
int	check_builtins(t_data *data, int is_parent)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);// keeps the standerd inputs in case of redirecting it
	fd[1] = dup(STDOUT_FILENO);// keeps the standerd outputs in case of redirecting it
	
	if (data->args == NULL)
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
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "env", 4) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_env(env_list_to_table());
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "exit", 5) == 0)
	{
		if(is_parent)
			printf("exit");
		close(fd[0]);
		close(fd[1]);
		exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_cd(data);
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_echo(data);
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "unset", 6) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_unset(data);
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "export", 7) == 0)
	{
		if (is_parent && data->in_files != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		ft_export(data);
		// exiter(data, 0);
	}
	else
	{
		// fprintf(stderr, "check builtins will return -1\n");///////////

		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	if (!is_parent)
		exiter(data, 0);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
