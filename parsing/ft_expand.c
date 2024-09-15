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

int	check_res_whitepaces(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i - 1] != quote)
				i++;
		}
		else
		{
			if (ft_iswhitespace(str[i]) == 1)
				return (0);
			i++;
		}
	}
	return (1);
}

int	heredoc(t_data *data, int *i, char **res)
{
	if (ft_strncmp(data->files->redirection, "<<", 3) != 0 && data->files->file)
	{
		while (data->files->file[*i])
			quote_checker(data->files->file, res, i, 1);
		if (*res == NULL)
			data->files->heredoc_fd = -1;
		if (data->files->file[0] != '\"' && data->files->file[0] != '\''
			&& !check_res_whitepaces(*res))
			data->files->heredoc_fd = -1;
		*res = NULL;
		*i = 0;
		while (data->files->file[*i])
			quote_checker(data->files->file, res, i, 0);
		if (data->files->heredoc_fd != -1)
			data->files->file = ft_strdup(*res);
		*res = NULL;
	}
	else if (!ft_strncmp(data->files->redirection, "<<", 3)
		&& data->files->file)
	{
		data->files->heredoc_fd = open_heredoc(data->files->file);
		if (data->files->heredoc_fd == -1)
			return (0);
	}
	return (1);
}

int	expand_file(t_data *data)
{
	t_files_list	*tmp;
	int				i;
	char			*res;

	res = NULL;
	while (data)
	{
		tmp = data->files;
		while (data->files)
		{
			i = 0;
			if (heredoc(data, &i, &res) == 0)
				return (0);
			data->files = data->files->next;
		}
		data->files = tmp;
		data = data->next;
	}
	return (1);
}

char	*export_handle(char *arg)
{
	char	*res;
	int		i_eq;

	res = NULL;
	i_eq = 0;
	if (ft_strchr(arg, '=', &i_eq))
	{
		res = ft_strnjoin(res, arg, (i_eq + 1));
		if (!ft_strchr(res, '$', NULL) && ft_strchr(arg + i_eq, '$', NULL))
		{
			res = ft_strnjoin(res, quotes_adder(arg + (i_eq + 1)), 0);
			return (res);
		}
	}
	return (arg);
}

void	expand(t_data *data)
{
	int		i;
	int		j;
	char	**res;
	char	**args_res;

	while (data)
	{
		i = -1;
		res = NULL;
		args_res = NULL;
		while (data->args && data->args[++i])
		{
			if (!ft_strncmp("export", data->args[0], ft_strlen(data->args[0])))
				data->args[i] = export_handle(data->args[i]);
			res = catch_expnad(data->args[i]);
			if (res && *res)
			{
				j = 0;
				while (res[j])
					args_res = ft_tablejoin(args_res, res[j++]);
			}
		}
		data->args = args_res;
		data = data->next;
	}
}
