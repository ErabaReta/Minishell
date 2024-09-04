/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:03:44 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 22:40:53 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	includes_option_n(char **args, int *start)
{
	int	i;
	int	mode;
	int	j;

	i = 1;
	mode = 0;
	while (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		else
			mode = 1;
		i++;
	}
	*start = i;
	return (mode);
}

int	ft_echo(t_data *data)
{
	int	mode;
	int	i;
	int	j;

	mode = includes_option_n(data->args, &i);
	while (data->args[i] != NULL)
	{
		j = 0;
		while (data->args[i][j] != '\0')
		{
			if (data->args[i][j] != '\n' || mode == 0)
				write(STDOUT_FILENO, &data->args[i][j], 1);
			j++;
		}
		i++;
		if (data->args[i] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (mode == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
