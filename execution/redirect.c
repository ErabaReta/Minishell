/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:02:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 01:18:48 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_files(t_files_list *files, int is_parent)
{
	int in_fd = -1;
	int out_fd = -1;
	int status;

	if (files == NULL)
		return 1;
	while (files != NULL)
	{
		status = 0;
		if (files->redirection[0] == '<')
			status += open_infile(files, &in_fd);
		else
			status += open_outfile(files, &out_fd);
		if (status != 0)
		{
			if (is_parent)
				return (1);
			exiter(1);
		}
		files = files->next;
	}
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return (0);
}


//opens the file after checking it existence and its permission then redirect the standard intput to it
int	open_infile(t_files_list *file, int *fd)
{
	if (*fd != -1)
		close(*fd);
	if (ft_strncmp(file->redirection, "<<", 3) == 0)
	{
		*fd = file->heredoc_fd;
	}
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
			return (1);
		}
	}
	// else if (access(file->file, F_OK) == 0) // it exist
	// {
	// 	if (is_dir(file->file))
	// 	{
	// 		print_err("minishell: ");
	// 		print_err(file->file);
	// 		print_err(": Is a directory\n");
	// 		return (1);
	// 	}
	// 	if (access(file->file, R_OK) == 0)// can be writen to it
	// 	{
	// 		*fd = open(file->file, O_RDONLY);//TODO protect failing
	// 		if (*fd < 0)
	// 		{
	// 			// printf("minishell: %s: failed to open file\n", tmp->file);//TODO custume ERR here
	// 			print_err("minishell: ");
	// 			print_err(file->file);
	// 			print_err(": failed to open file\n");
	// 			return (1);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		// printf("Minishell: permission denied: %s\n", tmp->file);
	// 		print_err("minishell: permission denied: ");
	// 		print_err(file->file);
	// 		print_err("\n");
	// 		return (1);
	// 	}
	// }
	// else
	// {
	// 	print_err("minishell: ");
	// 	print_err(file->file);
	// 	print_err(": No such file or directory\n");
	// 	return (1);
	// }
	// fprintf(stderr, "returnin\n");
	return (0);
}

//opens the file after checking it existence and its permission then redirect the standard output to it
int	open_outfile(t_files_list *file, int *fd)
{
	if (*fd != -1)
		close(*fd);
	if (file->heredoc_fd == -1)
	{
		print_err("minishell: ambiguous redirect\n");
		return (1);
	}
	if (access(file->file, F_OK) == 0 && is_dir(file->file))
	{
		print_err("minishell: ");
		print_err(file->file);
		print_err(": Is a directory\n");
		return (1);
	}
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
			return (1);
		}
	}
	// else if (access(file->file, F_OK) == 0) // it exist
	// {
	// 	if (is_dir(file->file))
	// 	{
	// 		print_err("minishell: ");
	// 		print_err(file->file);
	// 		print_err(": Is a directory\n");
	// 		return (1);
	// 	}
	// 	if (access(file->file, W_OK) == 0)// can be writen to it
	// 	{
	// 		if (ft_strncmp(file->redirection, ">", 2) == 0)
	// 			*fd = open(file->file, O_WRONLY | O_TRUNC);// TODO protect failing
	// 		else
	// 			*fd = open(file->file, O_WRONLY | O_APPEND);// TODO protect failing
	// 		if (*fd < 0)
	// 		{
	// 			// printf("minishell: %s: failed to open file\n", tmp->file);//TODO custume ERR here
	// 			print_err("minishell: ");
	// 			print_err(file->file);
	// 			print_err(": failed to open file\n");
	// 			return (1);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		// printf("Minishell: permission denied: %s\n", tmp->file);
	// 		print_err("minishell: permission denied: ");
	// 		print_err(file->file);
	// 		print_err("\n");
	// 		return (1);
	// 	}
	// }
	// else
	// {
	// 	if (ft_strncmp(file->redirection, ">", 2) == 0)
	// 		*fd = open(file->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);// TODO  protect failing
	// 	else
	// 		*fd = open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0644);// TODO  protect failing	
	// 	if (*fd < 0)
	// 	{
	// 		// printf("minishell: %s: No such file or directory\n",tmp->file);//TODO custume ERR here
	// 		print_err("minishell: ");
	// 		print_err(file->file);
	// 		print_err(": No such file or directory\n");
	// 		exiter(1);
	// 	}
	// }
	return (0);
}

void	sighandler_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		printf("quit (core dumped)\n");
	}
}

void	sig_exit_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
}

void	preparation_before_cmd()
{
				if (env_search("SHLVL") != NULL && ft_atoi(env_search("SHLVL")->value) - 1 >= 1000)
			{
				print_err("minishell: warning: shell level (");
				print_err(ft_itoa(ft_atoi(env_search("SHLVL")->value) - 1, 0));
				print_err(") too high, resetting to 1\n");
			}
	setup_signal_handler(1, SIG_IGN, sighandler_exev);
}


// closing all the not needed pipes and redirect the needed ones
int	piping(int a_pipe[2], int length, int i, int fd_out)
{
	preparation_before_cmd();
	if (length < 2)
		return 1;
	if (i == 0)
	{
		dup2(a_pipe[PIPE_INPUT], STDOUT_FILENO);
		close(a_pipe[PIPE_INPUT]);
		close(a_pipe[PIPE_OUTPUT]);
	}
	else if (i != 0 && i != length - 1)
	{
		dup2(a_pipe[PIPE_INPUT], STDOUT_FILENO);
		close(a_pipe[PIPE_INPUT]);
		dup2(fd_out, STDIN_FILENO);
		close(fd_out);
		close(a_pipe[PIPE_OUTPUT]);
	}
	else if (i == length -1)
	{
		dup2(fd_out, STDIN_FILENO);
		close(fd_out);
	}
	return (1);
}
