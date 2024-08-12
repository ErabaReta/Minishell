/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:11 by hunter            #+#    #+#             */
/*   Updated: 2024/08/12 17:26:55 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*reds_check(char **reds, t_data *curr, int i)
{
	int	j;

	j = 0;
	while (reds[j])
	{
		if (ft_strncmp(curr->args[i], reds[j], 2) == 0
			&& curr->args[i + 1] == NULL)
			return (printf("syntax error near unexpected token %s\n"
					, curr->args[i]), NULL);
		j++;
	}
	return (curr);
}

t_data	*syntax_error_red(t_data *data)
{
	int		i;
	t_data	*curr;
	char	**reds;

	reds = ft_split("< << > >>", ' ');
	curr = data;
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			if (reds_check(reds, curr, i) == NULL)
				return (NULL);
			i++;
		}
		curr = curr->next;
	}
	return (data);
}

t_data	*syntax_error_pipe(t_data *data)
{
	t_data	*curr;

	curr = data;
	while (curr)
	{
		if (curr->next != NULL)
			if (curr->next->args[0] == NULL || curr->args[0] == NULL)
				return (printf("syntax error near unexpected token `|'\n")
					, NULL);
		curr = curr->next;
	}
	return (data);
}

t_data	*syntax_error_her(t_data *data)
{
	t_data			*first;
	t_files_list	*curr;
	t_spec			*svars;
	int		her_num;

	svars = get_specials();
	her_num = 0;
	first = data;
	while (data)
	{
		curr = data->in_files;
		while (data->in_files)
		{
			if (ft_strncmp(data->in_files->redirection, "<<", 2) == 0)
				her_num++;
			data->in_files = data->in_files->next;
		}
		data->in_files = curr;
		data = data->next;
	}
	if (her_num > 16)
	{
		svars->exit_status = 2;
		printf("maximum here-document count exceeded\n");
		exiter(data, 2);
	}
	return (first);
}