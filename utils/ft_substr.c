/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:09:50 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/07 15:47:48 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	chars_counter(size_t s_len, size_t start, size_t len)
{
	if ((s_len - start) > len)
		return (len);
	return (s_len - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;
	size_t	count;

	count = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len == 0 || start >= s_len)
	{
		ptr = (char *)mallocate(sizeof(char));
	}
	else
	{
		count = chars_counter(s_len, start, len);
		ptr = (char *)mallocate((count + 1) * sizeof(char));
	}
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
		ptr[i] = s[start + i];
	ptr[i] = '\0';
	return (ptr);
}
