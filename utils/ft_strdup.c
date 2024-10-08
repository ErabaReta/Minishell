/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:52:38 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/17 20:40:36 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// FIXME not practical
char	*ft_strdup2(const char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)mallocate((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
