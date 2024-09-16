/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:48:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/16 15:29:43 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_fd	**get_fd_pool(void)
{
	static t_fd	*head;

	return (&head);
}

// store the fd to close later
void	store_fd(int fd)
{
	t_fd	**pool;
	t_fd	*new;

	new = (t_fd *)mallocate(sizeof(t_fd));
	new->fd = fd;
	pool = get_fd_pool();
	if (new != NULL)
	{
		new->next = *pool;
		*pool = new;
	}
}

// close all fds stored by FD POOL
void	clean_pool(void)
{
	t_fd	**pool;
	t_fd	*tmp;

	pool = get_fd_pool();
	while (*pool != NULL)
	{
		tmp = *pool;
		(*pool) = (*pool)->next;
		if (tmp->fd >= 0)
			close(tmp->fd);
		ft_free(tmp);
	}
}

static int	check_first(int fd, t_fd **pool, t_fd *tmp)
{
	if (fd == tmp->fd)
	{
		*pool = tmp->next;
		if (tmp->fd >= 0)
			close(tmp->fd);
		ft_free(tmp);
		return (1);
	}
	return (0);
}

// close specefic fd stored in fd pool
void	ft_close(int fd)
{
	t_fd	**pool;
	t_fd	*tmp;
	t_fd	*to_close;

	pool = get_fd_pool();
	tmp = *pool;
	if (tmp == NULL)
		return ;
	if (check_first(fd, pool, tmp))
		return ;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->next->fd == fd)
		{
			to_close = tmp->next;
			tmp->next = tmp->next->next;
			if (to_close->fd >= 0)
				close(to_close->fd);
			ft_free(to_close);
			return ;
		}
		tmp = tmp->next;
	}
}
