/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabledup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:10:45 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/04 03:10:47 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tabledup(char **table)
{
	int		i;
	char	**res;

	i = 0;
	if (table == NULL)
		return (NULL);
	while (table[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (table[i])
	{
		res[i] = ft_strdup(table[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
