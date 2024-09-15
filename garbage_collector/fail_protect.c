/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_protect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:07:15 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 20:20:47 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safer_pipe(int _pipe[2])
{
	if (pipe(_pipe) == -1)
	{
		perror("minishell");
		exiter(1);
	}
	store_fd(_pipe[PIPE_INPUT]);
	store_fd(_pipe[PIPE_OUTPUT]);
}

pid_t	safer_fork(void)
{
	pid_t	returned;

	returned = fork();
	if (returned == -1)
	{
		perror("minishell");
		exiter(1);
	}
	return (returned);
}

int	safer_dup(int _fd)
{
	int	returned;

	returned = dup(_fd);
	if (returned == -1)
	{
		perror("minishell");
		exiter(1);
	}
	store_fd(returned);
	return (returned);
}

int	safer_dup2(int _fd, int _fd2)
{
	int	returned;

	returned = dup2(_fd, _fd2);
	if (returned == -1)
	{
		perror("minishell");
		exiter(1);
	}
	return (returned);
}

__sighandler_t	safer_signal(int _sig, __sighandler_t _handler)
{
	__sighandler_t	returned;

	returned = signal(_sig, _handler);
	if (returned == SIG_ERR)
	{
		perror("minishell");
		exiter(1);
	}
	return (returned);
}
