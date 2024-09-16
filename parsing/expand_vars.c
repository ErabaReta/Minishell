/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/12 10:48:40 by ayechcha          #+#    #+#             */
/*   Updated: 2024/09/12 13:01:12 by ayechcha         ###   ########.fr       */
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

char	*find_expand(char *find, int q)
{
	t_spec	*svars;
	t_env	*env;

	svars = get_specials();
	env = svars->env;
	while (env)
	{
		if (!ft_strncmp(env->var, find, ft_strlen(env->var) + 1) && q == 0)
			return (ft_strdup(env->value));
		else if (!ft_strncmp(env->var, find, ft_strlen(env->var) + 1)
			&& q == 1)
			return (quotes_adder_toquote(ft_strdup(env->value)));
		env = env->next;
	}
	return (NULL);
}

int	isdou(char c)
{
	if (c == '?' || c == '_' || c == '$')
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
	if (arg[*i - 1] == '$')
		return (ft_strdup("$$"));
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

void	var_to_val(char *arg, int *i, char **res, int q)
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
		exp = find_expand(exp, q);
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
