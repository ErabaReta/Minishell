/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:55:13 by ayechcha          #+#    #+#             */
/*   Updated: 2024/07/31 19:55:13 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*lim_writer(char *str, int *start, char *cmd)
{
	int		end;

	if (str[*start] == '\"' || str[*start] == '\'')
	{
		end = ++(*start);
		while (str[end] != str[*start - 1] && str[end])
			end++;
		if (str[end] == '\0')
			return (NULL);
		cmd = ft_strnjoin(cmd, ft_substr(str, *start, (end - (*start))), 0);
		*start = end + 1;
	}
	else if (str[(*start)] == '$')
	{
		(*start)++;
		if (str[*start] != '\"' && str[*start] != '\'')
		{
			cmd = ft_strnjoin(cmd, str + ((*start) - 1), 2);
			(*start)++;
		}
	}
	else
		cmd = ft_strnjoin(cmd, str + (*start)++, 1);
	return (cmd);
}

char	*quotes_remove(char *str, int *exp)
{
	int		start;
	char	*cmd;

	cmd = NULL;
	start = 0;
	*exp = 0;
	while (str[start])
		cmd = lim_writer(str, &start, cmd);
	return (cmd);
}

char	*quotes_adder_toquote(char *str)
{
	int		i;
	char	*res;
	char	*quote;

	i = 0;
	res = NULL;
	quote = ft_strchr(str, '\'', NULL);
	if (quote)
	{
		while (str[i])
		{
			if (str[i] != '\'')
				res = ft_strnjoin(res, str + i, 1);
			else
				res = ft_strnjoin(res, "\"\'\"", 0);
			i++;
		}
	}
	else
		return (str);
	return (res);
}

char	*quotes_adder(char *str)
{
	char	*res;

	res = ft_strdup("\"");
	res = ft_strnjoin(res, str, 0);
	res = ft_strnjoin(res, "\"", 0);
	return (res);
}

char	*last_arg(char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
