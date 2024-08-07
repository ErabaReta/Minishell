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

char	*find_expand(char **env, char *find)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == find[j] && env[i][j] != '=')
			j++;
		if (env[i][j] == '=' && find[j] == '\0')
		{
			res = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	is_DOU(char c)
{
	if (c == '$' || c == '_')
		return (1);
	return (0);
}

char	*expand_DOR(char *arg, int *i)
{
	*i = *i + 2;
	if (!(isalnum(arg[*i]) && arg[*i] != '$' && arg[*i] != '\0' && arg[*i] != '\"' && arg[*i] != '\''))
		return(last_arg(NULL));
	while (isalnum(arg[*i]) && arg[*i] != '$' && arg[*i] != '\0' && arg[*i] != '\"' && arg[*i] != '\'')
		(*i)++;
	return (NULL);
}

void	var_to_val(char *arg, int *i, char **res, char **env)
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
		exp = find_expand(env, exp);
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

void	expand_out_file(t_data *data, char **env)
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
				var_to_val(data->out_files->file, &i, &res, env);
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

void	expand_in_file(t_data *data, char **env)
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
					var_to_val(data->in_files->file, &i, &res, env);
				if (res != NULL)
					data->in_files->file = ft_strdup(res);
				res = NULL;
			}
			else
				data->in_files->heredoc_fd = open_heredoc(data->in_files->file, env);
			data->in_files = data->in_files->next;
		}
		data->in_files = tmp;
		data = data->next;
	}
}

void	expand(t_data *data, char **env)
{
	int		i;
	char	*res;

	res = NULL;
	while (data)
	{
		i = 0;
		while (data->args && data->args[i])
		{
			res = catch_expnad(data->args[i], env);
			data->args[i] = ft_strdup(res);
			if (i > 0 && data->args[i - 1] == NULL)
			{
				data->args[i - 1] = data->args[i];
				data->args[i] = NULL;
			}
			res = NULL;
			i++;
		}
		data = data->next;
	}
}
