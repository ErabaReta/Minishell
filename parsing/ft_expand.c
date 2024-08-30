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

int	heredoc(t_data *data, int *i, char **res, int j)
{
	char	quote;

	if (ft_strncmp(data->files->redirection, "<<", 2) != 0)
	{
		while (data->files->file[*i])
			quote_checker(data->files->file , res, i, 1);
		if (*res == NULL)
			data->files->heredoc_fd = -1;
		while (*res && res[0][j])
		{
			if (res[0][j] == '\"' || res[0][j] == '\'')
			{
				quote = res[0][j];
				j++;
				while (res[0][j] != quote)
					j++;
				j++;
			}
			if (ft_iswhitespace(res[0][j]))
				data->files->heredoc_fd = -1;
			if (res[0][j])
				j++;
		}
		*res = NULL;
		*i = 0;
		while (data->files->file[*i])
			quote_checker(data->files->file , res, i, 0);
		if (data->files->heredoc_fd != -1)
			data->files->file = ft_strdup(*res);
		*res = NULL;
	}
	else
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
	int				j;
	char			*res;

	res = NULL;
	while (data)
	{
		tmp = data->files;
		while (data->files)
		{
			i = 0;
			j = 0;
			if (heredoc(data, &i, &res, j) == 0)
				return (0);
			data->files = data->files->next;
		}
		data->files = tmp;
		data = data->next;
	}
	return (1);
}


void	expand(t_data *data)
{
	int		i;
	int		j;
	char	**res;
	char	**args_res;

	while (data)
	{
		i = 0;
		res = NULL;
		args_res = NULL;
		while (data->args && data->args[i])
		{
			res = catch_expnad(data->args[i]);
			if (*res)
			{
				j = 0;
				while (res[j])
					args_res = ft_tablejoin(args_res, res[j++]);
			}
			i++;
		}
		data->args = args_res;
		data = data->next;
	}
}
