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

char	*ft_substr_withoutspace(char const *s)
{
	int		start;
	char	*res;

	res = NULL;
	start = 0;
	while (ft_iswhitespace(s[start]) && s[start])
		start++;
	while (s[start])
	{
		while (s[start] && !ft_iswhitespace(s[start]))
		{
			res = ft_strnjoin(res, s + start, 1);
			start++;
		}
		while (ft_iswhitespace(s[start]) && s[start])
			start++;
		if (s[start])
			res = ft_strnjoin(res, " ", 1);
	}
	return (res);
}

char	*find_expand(char *arg, char *find)
{
	t_spec	*svars;
	t_env	*env;

	svars = get_specials();
	env = svars->env;
	while (env)
	{
		if (!ft_strncmp(env->var, find, ft_strlen(env->var) + 1) && arg[0] == '\"')
			return (ft_strdup(env->value));
		if (!ft_strncmp(env->var, find, ft_strlen(env->var) + 1))
			return (ft_substr_withoutspace(ft_strdup(env->value)));
		env = env->next;
	}
	return (NULL);
}

int	isdou(char c)
{
	if (c == '?' || c == '_')
		return (1);
	return (0);
}

char	*expanddor(char *arg, int *i)
{
	t_spec	*svars;

	svars = get_specials();
	*i += 2;
	if (arg[*i - 1] == '?')
		return (ft_itoa(svars->exit_status, 0));
	if (ft_isalnum(arg[*i]) == 0)
	{
		if (arg[*i - 1] == '_')
			return (env_search("_")->value);
	}
	while (isalnum(arg[*i]) && arg[*i] != '$' && arg[*i] != '\0'
		&& arg[*i] != '\"' && arg[*i] != '\'')
		(*i)++;
	return (NULL);
}

void	var_to_val(char *arg, int *i, char **res)
{
	int		end;
	char	*exp;

	end = 0;
	if (arg[*i] == '$' && ft_isalnum(arg[*i + 1]))
	{
		end = ++(*i);
		while (arg[end] != '$' && arg[end] != '\0' && arg[end] != '\"'
			&& arg[end] != '\'' && ft_isalnum(arg[end]))
			end++;
		exp = ft_substr(arg, *i, end - *i);
		exp = find_expand(arg, exp);
		*res = ft_strnjoin(*res, exp, 0);
		exp = NULL;
		*i = end;
	}
	else if (arg[*i] == '$' && isdou(arg[*i + 1]))
		*res = ft_strnjoin(*res, expanddor(arg, i), 0);
	else if (arg[*i] == '$' && (arg[*i + 1] == '\"' || arg[*i + 1] == '\''))
		(*i)++;
	else
	{
		*res = ft_strnjoin(*res, arg + *i, 1);
		(*i)++;
	}
}

int	quote_checker(char *arg, char **res, int *i, int q)
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
		if (q == 0)
		{
			*res = ft_strnjoin(*res, ft_strdup(""), 0);
			(*i)++;
			while (arg[*i] != '\"' && arg[*i])
				var_to_val(arg, i, res);
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
			*res = ft_strnjoin(*res, arg + (*i), 1);
			(*i)++;
		}
	}
	else
	{
		var_to_val(arg, i, res);
		return (1);
	}
	return (0);
}

char	**arg_spliter(char *str)
{
	int		start;
	int		end;
	char	quote;
	char	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	start = 0;
	while (str && str[start])
	{
		while (str[start] && ft_iswhitespace(str[start]) == 1)
		{
			start++;
		}
		while (str[start] && str[start] != '|' && ft_iswhitespace(str[start]) == 0)
		{
			quote = '\0';
			end = start;
			while (str[end] && ft_iswhitespace(str[end]) == 0 && quote == '\0')
			{
				if (str[end] == '\"' || str[end] == '\'')
				{
					quote = str[end];
					cmd = ft_strnjoin(cmd, str + end, 1);
					end++;
					while (str[end] != quote && str[end])
					{
						cmd = ft_strnjoin(cmd, str + end, 1);
						end++;
					}
					cmd = ft_strnjoin(cmd, str + end, 1);
				}
				else
					cmd = ft_strnjoin(cmd, str + end, 1);
				quote = '\0';
				end++;
			}
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
	j = 0;
	str = NULL;
	ex_res = NULL;
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
