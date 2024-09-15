/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:02:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 20:02:11 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_to_files(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		safer_dup2(in_fd, STDIN_FILENO);
		ft_close(in_fd);
	}
	if (out_fd != -1)
	{
		safer_dup2(out_fd, STDOUT_FILENO);
		ft_close(out_fd);
	}
}

int	handle_files(t_files_list *files, int is_parent)
{
	int	in_fd;
	int	out_fd;
	int	status;

	in_fd = -1;
	out_fd = -1;
	if (files == NULL)
		return (1);
	while (files != NULL)
	{
		status = 0;
		if (files->redirection[0] == '<')
			status += open_infile(files, &in_fd, out_fd);
		else
			status += open_outfile(files, &out_fd, in_fd);
		if (status != 0)
		{
			if (is_parent)
				return (1);
			exiter(1);
		}
		files = files->next;
	}
	redirect_to_files(in_fd, out_fd);
	return (0);
}

int	open_infile(t_files_list *file, int *fd, int other_fd)
{
	if (*fd != -1)
		ft_close(*fd);
	if (ft_strncmp(file->redirection, "<<", 3) == 0)
		*fd = file->heredoc_fd;
	else if (file->heredoc_fd == -1)
	{
		print_err("minishell: ambiguous redirect\n");
		return (1);
	}
	else
	{
		*fd = open(file->file, O_RDONLY);
		if (*fd == -1)
		{
			print_err("minishell: ");
			perror(file->file);
			if (other_fd != -1)
				ft_close(other_fd);
			return (1);
		}
		store_fd(*fd);
	}
	return (0);
}

int	open_outfile(t_files_list *file, int *fd, int other_fd)
{
	if (*fd != -1)
		ft_close(*fd);
	if (file->heredoc_fd == -1)
		return (print_err("minishell: ambiguous redirect\n") + 1);
	else
	{
		if (ft_strncmp(file->redirection, ">", 2) == 0)
			*fd = open(file->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			*fd = open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (*fd == -1)
		{
			print_err("minishell: ");
			perror(file->file);
			if (other_fd != -1)
				ft_close(other_fd);
			return (1);
		}
		store_fd(*fd);
	}
	return (0);
}

int	piping(int a_pipe[2], int length, int i, int fd_out)
{
	setup_signal_handler(1, SIG_IGN, SIG_DFL);
	if (length < 2)
		return (1);
	if (i == 0)
	{
		safer_dup2(a_pipe[PIPE_INPUT], STDOUT_FILENO);
		ft_close(a_pipe[PIPE_INPUT]);
		ft_close(a_pipe[PIPE_OUTPUT]);
	}
	else if (i != 0 && i != length - 1)
	{
		safer_dup2(a_pipe[PIPE_INPUT], STDOUT_FILENO);
		ft_close(a_pipe[PIPE_INPUT]);
		safer_dup2(fd_out, STDIN_FILENO);
		ft_close(fd_out);
		ft_close(a_pipe[PIPE_OUTPUT]);
	}
	else if (i == length -1)
	{
		safer_dup2(fd_out, STDIN_FILENO);
		ft_close(fd_out);
	}
	return (1);
}
