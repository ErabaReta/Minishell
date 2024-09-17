/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:13:32 by ayechcha          #+#    #+#             */
/*   Updated: 2024/09/17 20:40:36 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*ft_lstlast(t_data *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_data	*ft_lstnew(void)
{
	t_data	*new;

	new = (t_data *)mallocate(sizeof(t_data));
	new->prev = NULL;
	new->next = NULL;
	new->files = NULL;
	return (new);
}

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	if (lst != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
			new->prev = last;
			new->next = NULL;
		}
	}
}
