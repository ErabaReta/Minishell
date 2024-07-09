/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:25:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/09 14:38:34 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// checks is the cmd is builtin than execute it
int	check_builtins(t_data *data, int is_parent)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);// keeps the standerd inputs in case of redirecting it
	fd[1] = dup(STDOUT_FILENO);// keeps the standerd outputs in case of redirecting it
	if (ft_strncmp(data->args[0], "pwd", 4) == 0)
	{
		if (is_parent && data->in_files[0] != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		pwd();
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "exit", 5) == 0)
	{
		if(is_parent)
			printf("exit");
		exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
	{
		if (is_parent && data->in_files[0] != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		cd(data);
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
	{
		if (is_parent && data->in_files[0] != NULL)
			open_infiles(data);
		if (is_parent && data->out_files != NULL)
			open_outfiles(data);
		echo(data);
		// exiter(data, 0);
	}
	else
	{
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
