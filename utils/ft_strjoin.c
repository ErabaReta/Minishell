/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:29:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/06/27 16:29:30 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char  *ft_strcut(char const *str, int len)
{
  int    i;
  char  *res;

  i = 0;
  if (len == 0)
    return (ft_strdup(str));
  res = (char *)malloc(len + 1);
  while (str[i] && i < len)
  {
    res[i] = str[i];
    i++;
  }
  res[i] = '\0';
  return (res);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strcut(s2, len));
	if (s2 == NULL)
		return (ft_strdup(s1));
  if (len == 0)
      len = ft_strlen(s2);
	ptr = (char *)malloc((ft_strlen(s1) + (len + 1)) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j] != '\0' && j < len)
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}
