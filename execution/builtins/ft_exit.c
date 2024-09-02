/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:51:53 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/02 16:47:41 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_exit_arg(char *arg)
{
	size_t	r;
	int		i;
	int		signe;

	r = 0;
	i = 0;
	signe = 1;
	while (ft_iswhitespace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i++] == '-')
			signe = -1;
	}
	while (ft_isdigit(arg[i]) == 1)
	{
		r = r * 10 + (arg[i++] - '0');
		if ((r > 9223372036854775807 && signe == 1)
			|| (r >= 9223372036854775807 && signe == -1))
		{
			print_err("minishell: exit: ");
			print_err(arg);
			print_err(": numeric argument required\n");
			exiter(2);
		}
	}
	while (ft_iswhitespace(arg[i]))
		i++;
	if (!ft_isdigit(arg[i]) && !ft_iswhitespace(arg[i]) && arg[i] != '\0')
	{
		print_err("minishell: exit: ");
		print_err(arg);
		print_err(": numeric argument required\n");
		exiter(2);
	}
	exiter(((long)r * signe) & 255);
}

void	ft_exit(t_data *data, int is_parent, int *fd, int *exit_status)
{
	// (void)data;
	if (data->args[1] == NULL)
	{
		if(is_parent)
			print_err("exit\n");
		close(fd[0]);
		close(fd[1]);
		exiter(*exit_status);
	}
	else if (data->args[2] != NULL)
	{
		if(is_parent)
			print_err("exit\n");
		print_err("minishell: exit: too many arguments\n");
		if (!is_parent)
			exiter(1);
		else
		{
			*exit_status = 1;
			return ;
		}
	}
	else
		pars_exit_arg(data->args[1]);
}