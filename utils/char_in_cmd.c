/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_in_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:49:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/17 20:40:36 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns the indice of a char inside a cmd 
//(it ignore ones inside qoutes and double qoutes)
int	char_in_cmd(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"')
		{
			while (cmd[i] != '\0' && cmd[i] != '\"')
				i++;
		}
		if (cmd[i] == '\'')
		{
			while (cmd[i] != '\0' && cmd[i] != '\'')
				i++;
		}
		if (cmd[i] == c)
			return (i);
		if (cmd[i] != '\0')
			i++;
	}
	return (-1);
}
