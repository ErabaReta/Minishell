/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:56:47 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/07 20:11:44 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	indexer(char const *s, char c, size_t i, size_t *end_index)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	*end_index = i;
	return (i);
}

size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 1;
	count = 0;
	if (s == NULL || s[0] == '\0')
		return (0);
	if (s[0] != c)
		count++;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static void	*extracter(char *ptr, size_t *end_index, size_t *start_index,
		const char *s)
{
	ptr = (char *)mallocate(sizeof(char) * (*end_index - *start_index + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, s + *start_index, *end_index - *start_index);
	ptr[*end_index - *start_index] = '\0';
	*start_index = *end_index;
	return (ptr);
}

static void	*free_all(char **ptr, int i)
{
	while (i >= 0)
	{
		ft_free(ptr[i]);
		i--;
	}
	ft_free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	start_index;
	size_t	end_index;

	i = count_words(s, c);
	ptr = (char **)mallocate((i + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	start_index = 0;
	while (1)
	{
		while (s != NULL && s[start_index] == c && c != '\0')
			start_index++;
		if (s == NULL || start_index == indexer(s, c, start_index, &end_index))
		{
			ptr[i] = NULL;
			break ;
		}
		ptr[i] = extracter(ptr[i], &end_index, &start_index, s);
		if (ptr[i++] == NULL)
			return (free_all(ptr, --i));
	}
	return (ptr);
}
