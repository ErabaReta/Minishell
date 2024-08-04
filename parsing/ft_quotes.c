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

void	init_vars(char **cmd, int *start)
{
	*cmd = NULL;
	*start = 0;
}

char	*quotes_remove(char *str)
{
	int		start;
	int		end;
	char	*cmd;

	init_vars(&cmd, &start);
	while (str[start])
	{
		if (str[start] == '\"' || str[start] == '\'')
		{
			end = ++start;
			while (str[end] != str[start - 1] && str[end])
				end++;
			if (str[end] == '\0')
				return (NULL);
			cmd = ft_strnjoin(cmd, ft_substr(str, start - 1,
						(end - start) + 2), 0);
			start = end + 1;
		}
		else
		{
			cmd = ft_strnjoin(cmd, str + start, 1);
			start++;
		}
	}
	return (cmd);
}
