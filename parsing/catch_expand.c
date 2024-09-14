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

void	double_quote_exp(int q, char **res, char *arg, int *i)
{
	if (q == 0)
	{
		*res = ft_strnjoin(*res, ft_strdup(""), 0);
		(*i)++;
		while (arg[*i] != '\"' && arg[*i])
		{
			if (arg[*i] == '$' && !ft_isalnum(arg[*i + 1])
				&& !isdou(arg[*i + 1]))
				*res = ft_strnjoin(*res, arg + ((*i)++), 1);
			else
				var_to_val(arg, i, res, q);
		}
		(*i)++;
	}
	else
	{
		*res = ft_strnjoin(*res, arg + (*i), 1);
		(*i)++;
		while (arg[*i] != '\"' && arg[*i])
		{
			*res = ft_strnjoin(*res, arg + (*i), 1);
			(*i)++;
		}
		*res = ft_strnjoin(*res, arg + (*i)++, 1);
	}
}

void	quote_checker(char *arg, char **res, int *i, int q)
{
	int	end;

	if (arg[*i] == '\'')
	{
		if (q == 1)
			*res = ft_strnjoin(*res, arg + (*i), 1);
		end = ++(*i);
		while (arg[end] != '\'' && arg[end])
			end++;
		*res = ft_strnjoin(*res, ft_substr(arg, *i, end - *i), 0);
		if (arg[end] == '\'')
		{
			if (q == 1)
				*res = ft_strnjoin(*res, arg + end, 1);
			*i = ++end;
		}
	}
	else if (arg[*i] == '\"')
	{
		double_quote_exp(q, res, arg, i);
	}
	else
		var_to_val(arg, i, res, q);
}

char	*catch_space(char *str, int *end)
{
	char	*cmd;
	char	quote;

	cmd = NULL;
	quote = '\0';
	while (str[*end] && ft_iswhitespace(str[*end]) == 0 && quote == '\0')
	{
		if (str[*end] == '\"' || str[*end] == '\'')
		{
			quote = str[*end];
			cmd = ft_strnjoin(cmd, str + (*end), 1);
			(*end)++;
			while (str[*end] && str[*end] != quote)
			{
				cmd = ft_strnjoin(cmd, str + (*end), 1);
				(*end)++;
			}
		}
		cmd = ft_strnjoin(cmd, str + (*end), 1);
		quote = '\0';
		if (str[*end])
			(*end)++;
	}
	return (cmd);
}

char	**arg_spliter(char *str)
{
	int		start;
	int		end;
	char	quote;
	char	*cmd;
	char	**args;

	args = NULL;
	start = 0;
	while (str && str[start])
	{
		while (str[start] && ft_iswhitespace(str[start]) == 1)
			start++;
		while (str[start] && ft_iswhitespace(str[start]) == 0)
		{
			end = start;
			cmd = catch_space(str, &end);
			quote = '\0';
			if (cmd == NULL)
				return (NULL);
			start = end;
			args = ft_tablejoin(args, cmd);
			cmd = NULL;
		}
	}
	return (args);
}

char	**catch_expnad(char *arg)
{
	int		i;
	int		j;
	char	*ex_res;
	char	**res;
	char	*str;

	i = 0;
	str = NULL;
	while (arg[i])
		quote_checker(arg, &str, &i, 1);
	res = arg_spliter(str);
	i = 0;
	while (res && res[i])
	{
		j = 0;
		ex_res = NULL;
		while (res[i][j])
			quote_checker(res[i], &ex_res, &j, 0);
		res[i] = ex_res;
		i++;
	}
	return (res);
}
