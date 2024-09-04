/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:37:34 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 21:40:05 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_table(char **table, int lenght)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	if (lenght <= 1)
		return ;
	i = -1;
	while (++i < lenght - 1)
	{
		j = i;
		while (++j < lenght)
		{
			k = 0;
			while (table[i][k] == table[j][k])
				k++;
			if (table[i][k] > table[j][k])
			{
				tmp = table[i];
				table[i] = table[j];
				table[j] = tmp;
			}
		}
	}
}
