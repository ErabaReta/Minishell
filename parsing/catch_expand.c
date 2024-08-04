/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:07:33 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/01 22:07:33 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_checker(char *arg, char **res, char **env, int *i)
{
	int	end;

	end = 0;
	if (arg[*i] == '\'')
	{
		end = ++(*i);
		while (arg[end] != '\'' && arg[end])
			end++;
		*res = ft_strnjoin(*res, ft_substr(arg, *i, end - *i), 0);
		if (arg[end] == '\'')
			*i = ++end;
	}
	else if (arg[*i] == '\"')
	{
		(*i)++;
		while (arg[*i] != '\"' && arg[*i])
			var_to_val(arg, i, res, env);
		(*i)++;
	}
	else
		var_to_val(arg, i, res, env);
}

char	*catch_expnad(char *arg, char **env)
{
	int		i;
	int		end;
	char	*res;
	char	*exp;

	i = 0;
	end = 0;
	res = NULL;
	exp = NULL;
	while (arg[i])
	{
		quote_checker(arg, &res, env, &i);
	}
	return (res);
}
