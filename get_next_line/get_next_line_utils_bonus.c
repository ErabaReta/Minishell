/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:01:30 by eouhrich          #+#    #+#             */
/*   Updated: 2023/11/26 18:01:33 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	ptr = malloc((ft_strlen(s1, 2) + ft_strlen(s2, 2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j] != '\0')
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	free(s1);
	return (ptr);
}

int	ft_strlen(char *s, char mode)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n' && mode == 1)
			return (i);
		i++;
	}
	if (mode == 1)
		return (-1);
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;
	size_t	count;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s, 2);
	count = s_len - start;
	if (len < 0 || s_len == 0 || start >= s_len)
		ptr = (char *)malloc(sizeof(char));
	else
	{
		if ((s_len - start) > len)
			count = len;
		ptr = (char *)malloc((count + 1) * sizeof(char));
	}
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
		ptr[i] = s[start + i];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = ft_strlen((char *)s1, 2);
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
