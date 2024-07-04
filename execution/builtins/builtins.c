/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:25:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/04 15:04:01 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(t_data *data, int is_parent)
{
	if (ft_strncmp(data->args[0], "pwd", 4) == 0)
	{
		pwd();
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "exit", 5) == 0)
	{
		exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
	{
		cd(data);
		// exiter(data, 0);
	}
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
	{
		echo(data);
		// exiter(data, 0);
	}
	else
	{
		return (-1);
	}
	if (!is_parent)
		exiter(data, 0);
	return (0);
}
