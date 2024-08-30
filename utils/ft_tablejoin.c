/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablejoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:00:54 by ayechcha          #+#    #+#             */
/*   Updated: 2024/07/29 18:00:56 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tablejoin(char **table, char *new)
{
	int		i;
	char	**res;

	i = 0;
	if (new == NULL)
		return (table);
	if (table == NULL)
	{
		res = (char **)mallocate(sizeof(char *) * 2);
		res[0] = ft_strdup(new);
		res[1] = NULL;
		return (res);
	}
	while (table[i])
		i++;
	res = (char **)mallocate(sizeof(char *) * (i + 2));
	i = 0;
	while (table[i])
	{
		res[i] = ft_strdup(table[i]);
		i++;
	}
	res[i++] = ft_strdup(new);
	res[i] = NULL;
	return (res);
}

void	free_table(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		ft_free(args[i]);
		i++;
	}
	ft_free(args);
}

void	del_elem_char(t_data *data, int i)
{
	char	**new;
	int		size;
	int		deff;

	deff = 0;
	size = 0;
	while (data->args[size])
		size++;
	new = (char **)mallocate((sizeof(char *) * size) - 1);
	size = 0;
	while (data->args[size])
	{
		if (size == i)
			deff++;
		else
			new[size - deff] = ft_strdup(data->args[size]);
		size++;
	}
	free_table(data->args);
	data->args = new;
}

t_files_list	*add_last(t_files_list **head, t_files_list *new)
{
	t_files_list	*curr;

	if (*head == NULL)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (*head);
}

t_files_list	*make_new(char *redirection, char *file)
{
	t_files_list	*new;

	new = (t_files_list *)mallocate(sizeof(t_files_list));
	new->redirection = ft_strdup(redirection);
	new->file = ft_strdup(file);
	new->heredoc_fd = 0;
	new->next = NULL;
	return (new);
}
