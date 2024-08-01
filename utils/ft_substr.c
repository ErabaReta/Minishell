/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunter <hunter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:30:27 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/01 18:13:34 by hunter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t chars_counter(size_t s_len, size_t start, size_t len)
{
  if ((s_len - start) > len)
	  return (len);
	return (s_len - start);
}

char  *ft_substr(char const *s, unsigned int start, size_t len)
{
  char    *ptr;
  size_t  i;
  size_t  s_len;
  size_t  count;
  
  if (s == NULL)
    return (NULL);
  s_len = ft_strlen(s);
  count = 0;
  if (s_len == 0 || start >= s_len)
  {
    ptr = (char *)malloc(sizeof(char));
  }
  else
  {
    count = chars_counter(s_len, start, len);
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
