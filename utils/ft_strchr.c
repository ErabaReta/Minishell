/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:36 by ayechcha          #+#    #+#             */
/*   Updated: 2024/09/02 23:56:36 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c, int *index)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			if (index)
				*index = i;
			return ((char *)s);
		}
		i++;
		s++;
	}
	if ((char)c == '\0')
	{
		if (index)
			*index = i;
		return ((char *)s);
	}
	return (NULL);
}
