/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:48:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 17:03:19 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_fd	**get_fd_pool()
{
	static t_fd	*head;
	
	return (&head);
}

// add front
void	add_to_pool(t_fd *new)
{
	t_fd **pool;

	pool = get_fd_pool();
	if (new != NULL)
	{
		new->next = *pool;
		*pool = new;
	}
}

// store th fd to close later
void	store_fd(int fd)
{
	t_fd	*new;

	new = (t_fd *)mallocate(sizeof(t_fd));
	new->fd = fd;
	add_to_pool(new);
}

// close all fds stored by FD POOL
void	clean_pool()
{
	t_fd	**pool;
	t_fd	*tmp;

	pool = get_fd_pool();
	while (*pool != NULL)
	{
		tmp = *pool;
		(*pool) = (*pool)->next;
		close(tmp->fd);//
		ft_free(tmp);
	}
}
// close specefic fd allocated by fd pool
void	ft_close(int fd)
{
	t_fd	**pool;
	t_fd	*tmp;
	t_fd	*to_close;
	
	pool = get_fd_pool();
	tmp = *pool;
	if (tmp == NULL)
		return ;
	if (fd == tmp->fd)
	{
		*pool = tmp->next;
		close(tmp->fd);
		ft_free(tmp);
		return ;
	}
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->next->fd == fd)
		{
			to_close = tmp->next;
			tmp->next = tmp->next->next;
			close(to_close->fd);
			ft_free(to_close);
			return ;
		}
		tmp = tmp->next;
	}
}
//===== testing ===========
// int main()
// {
// 	int fd;
// 	int pipes[2];

// 	fd = open("input.txt", O_RDONLY);
// 	store_fd(fd);
// 	char *str = (char *)mallocate(10);
// 	char *str2 = (char *)mallocate(3);
// 	read(fd, str, 9);
// 	str[9] = '\0';
// 	pipe(pipes);
// 	store_fd(pipes[PIPE_INPUT]);
// 	store_fd(pipes[PIPE_OUTPUT]);

// 	write(pipes[PIPE_INPUT], str, 2);
// 	ft_close(pipes[PIPE_INPUT]);
// 	read(pipes[PIPE_OUTPUT], str2, 2);
// 	str2[2] = '\0';

// 	printf("%s\n", str2);

// 	clean_pool();
// 	free_all_heap();
// 	return (0);
	
	

	
// }