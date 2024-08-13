/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:25:46 by ayechcha          #+#    #+#             */
/*   Updated: 2024/07/31 11:25:48 by ayechcha         ###   ########.fr       */
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

char	*find_expand(char *find)
{
	t_spec	*svars;
	t_env	*env;

	svars = get_specials();
	env = svars->env;
	while (env)
	{
		if (!ft_strncmp(env->var, find, ft_strlen(env->var) + 1))
			return (ft_substr_withoutspace(ft_strdup(env->value)));
		env = env->next;
	}
	return (NULL);
}

int	is_DOU(char c)
{
	if (c == '?' || c == '_')
		return (1);
	return (0);
}

char	*expand_DOR(char *arg, int *i)
{
	t_spec	*svars;

	svars = get_specials();
	*i += 2;
	if (arg[*i - 1] == '?')
		return (ft_itoa(svars->exit_status));
	if (ft_isalnum(arg[*i]) == 0)
	{
		if (arg[*i - 1] == '_')
			return (env_search("_")->value);
	}
	while (isalnum(arg[*i]) && arg[*i] != '$' && arg[*i] != '\0' && arg[*i] != '\"' && arg[*i] != '\'')
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
		exp = find_expand(exp);
		*res = ft_strnjoin(*res, exp, 0);
		exp = NULL;
		*i = end;
	}
	else if (arg[*i] == '$' && is_DOU(arg[*i + 1]))
		*res = ft_strnjoin(*res, expand_DOR(arg, i), 0);
	else
	{
		*res = ft_strnjoin(*res, arg + *i, 1);
		(*i)++;
	}
}

void	expand_out_file(t_data *data)
{
	t_files_list	*tmp;
	int				i;
	char			*res;

	res = NULL;
	while (data)
	{
		tmp = data->out_files;
		while (data->out_files)
		{
			i = 0;
			while (data->out_files->file[i])
				var_to_val(data->out_files->file, &i, &res);
			if (res != NULL)
			{
				data->out_files->file = ft_strdup(res);
				res = NULL;
			}
			data->out_files = data->out_files->next;
		}
		data->out_files = tmp;
		data = data->next;
	}
}

int	expand_in_file(t_data *data)
{
	t_files_list	*tmp;
	int				i;
	char			*res;

	res = NULL;
	while (data)
	{
		tmp = data->in_files;
		while (data->in_files)
		{
			i = 0;
			if (ft_strncmp(data->in_files->redirection, "<<", 2) != 0)
			{
				while (data->in_files->file[i])
					var_to_val(data->in_files->file, &i, &res);
				if (res != NULL)
					data->in_files->file = ft_strdup(res);
				res = NULL;
			}
			else
				data->in_files->heredoc_fd = open_heredoc(data->in_files->file);
			if (data->in_files->heredoc_fd == -1)
				return (0);
			data->in_files = data->in_files->next;
		}
		data->in_files = tmp;
		data = data->next;
	}
	return (1);
}

void	expand(t_data *data)
{
	int		i;
	char	*res;
	char	**args_res;

	res = NULL;
	args_res = NULL;
	while (data)
	{
		i = 0;
		while (data->args && data->args[i])
		{
			res = catch_expnad(data->args[i]);
			if (i == 0)
			{
				args_res = ft_split(res, ' ');
			}
			else
				if (res)
					args_res = ft_tablejoin(args_res, res);
			res = NULL;
			i++;
		}
		data->args = args_res;
		data = data->next;
	}
}
