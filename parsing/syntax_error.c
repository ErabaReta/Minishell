/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:11 by hunter            #+#    #+#             */
/*   Updated: 2024/09/12 17:46:19 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*check_errors(t_data *data)
{
	t_spec	*svars;

	svars = get_specials();
	if (!syntax_error_pipe(data) || !syntax_error_red(data))
	{
		svars->exit_status = 2;
		return (NULL);
	}
	redirection(data);
	if (!syntax_error_her(data))
		return (NULL);
	expand(data);
	if (!expand_file(data))
		return (NULL);
	return (data);
}

t_data	*reds_check(char **reds, t_data *curr, int i)
{
	int		j;
	t_spec	*svars;

	j = 0;
	svars = get_specials();
	while (reds[j])
	{
		if (ft_strncmp(curr->args[i], reds[j], 2) == 0
			&& curr->args[i + 1] == NULL)
		{
			svars->exit_status = 2;
			return (printf("syntax error near unexpected token %s\n"
					, curr->args[i]), NULL);
		}
		j++;
	}
	return (curr);
}

t_data	*syntax_error_red(t_data *data)
{
	int		i;
	t_data	*curr;
	t_spec	*svars;
	char	**reds;

	reds = ft_split("< << > >>", ' ');
	curr = data;
	svars = get_specials();
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			if (reds_check(reds, curr, i) == NULL)
			{
				svars->exit_status = 2;
				return (NULL);
			}
			i++;
		}
		curr = curr->next;
	}
	return (data);
}

t_data	*syntax_error_pipe(t_data *data)
{
	t_data	*curr;
	t_spec	*svars;

	curr = data;
	svars = get_specials();
	while (curr)
	{
		if (curr->next != NULL)
		{
			if (curr->next->args[0] == NULL || curr->args[0] == NULL)
			{
				svars->exit_status = 2;
				return (printf("syntax error near unexpected token `|'\n")
					, NULL);
			}
		}
		curr = curr->next;
	}
	return (data);
}

int	syntax_error_her(t_data *data)
{
	t_files_list	*curr;
	t_spec			*svars;
	int				her_num;

	svars = get_specials();
	her_num = 0;
	while (data)
	{
		curr = data->files;
		while (data->files)
		{
			if (ft_strncmp(data->files->redirection, "<<", 2) == 0)
				her_num++;
			data->files = data->files->next;
		}
		data->files = curr;
		data = data->next;
	}
	if (her_num > 16)
	{
		svars->exit_status = 2;
		printf("maximum here-document count exceeded\n");
		exiter(2);
	}
	return (1);
}
