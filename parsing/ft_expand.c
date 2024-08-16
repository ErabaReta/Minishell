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

int	herdoc(t_data *data, int *i, char **res)
{
	if (ft_strncmp(data->in_files->redirection, "<<", 2) != 0)
	{
		while (data->in_files->file[*i])
			var_to_val(data->in_files->file, i, res);
		if (*res != NULL)
			data->in_files->file = ft_strdup(*res);
		*res = NULL;
	}
	else
		data->in_files->heredoc_fd = open_heredoc(data->in_files->file);
	if (data->in_files->heredoc_fd == -1)
		return (0);
	return (1);
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
			if (herdoc(data, &i, &res) == 0)
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
			if (i == 0 && data->args[i][0] != '\"')
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
