/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:14:03 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/18 18:25:47 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//returns 1 if there a whitespace in the string str, otherwise return 0
int	include_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '0')
	{
		if (ft_iswhitespace(str[i]))
			return (1);
		i++;
	}
	return (0);
}
