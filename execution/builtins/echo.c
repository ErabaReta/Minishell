/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:03:44 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/04 14:13:47 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	includes_option_n(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "-n", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	echo(t_data *data)
{
	int	mode;
	int	i;
	int	j;
	
	mode = includes_option_n(data->args);
	i = 1;
	while (data->args[i])
	{
		j = 0;
		while (ft_strncmp(data->args[i], "-n", 3) != 0 && data->args[i][j] )
		{
			if (data->args[i][j] != '\n' || mode == 0)
				write(STDOUT_FILENO, &data->args[i][j], 1);
			j++;
		}
		i++;
	}
	if (mode == 0)
		write(STDOUT_FILENO, "\n", 1);

}