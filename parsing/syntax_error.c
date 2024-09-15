/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:11 by hunter            #+#    #+#             */
/*   Updated: 2024/09/15 14:14:23 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*check_errors(t_data *data)
{
	t_spec	*svars;

	svars = get_specials();
	redirection(data);
	if (!syntax_error_red(data) || !syntax_error_pipe(data))
	{
		svars->exit_status = 2;
		return (NULL);
	}
	if (!syntax_error_her(data))
		return (NULL);
	expand(data);
	if (!expand_file(data))
		return (NULL);
	return (data);
}

t_data	*syntax_error_red(t_data *data)
{
	t_data			*curr;
	t_files_list	*tmp;

	curr = data;
	while (curr)
	{
		tmp = curr->files;
		while (curr->files)
		{
			if (curr->files->file == NULL)
			{
				get_specials()->exit_status = 2;
				printf("syntax error near unexpected token %s\n",
					curr->files->redirection);
				return (NULL);
			}
			curr->files = curr->files->next;
		}
		curr->files = tmp;
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
			if (curr->next->args == NULL && curr->next->files == NULL)
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
