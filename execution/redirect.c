/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:02:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/02 18:01:53 by eouhrich         ###   ########.fr       */
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
			// fprintf(stderr, "redirect %c || file %s\n");
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
	// fprintf(stderr, "in filed %d\n", in_fd);
	if (in_fd != -1)
	{
		// fprintf(stderr, "fd in duped\n");
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



// closing all the not needed pipes and redirect the needed ones
void	piping(t_data *data, int **pipes, int length, int i)
{
	int j = 0;

	while (j < length - 1) // closing all the not needed pipes
	{
		if (j != i)
		{
			close(pipes[j][PIPE_INPUT]);
			// printf("closing the input of pipe %d in child %d\n", j, i);
		}
		if ( j != i - 1)
		{
			close(pipes[j][PIPE_OUTPUT]);
			// printf("closing the output of pipe %d in child %d\n", j, i);
		}
		j++;
	}
	if (i != 0) // change the input to be the output of cmd before exept if this is the not first cmd
	{
			
			// fprintf(stderr, "cmd => \"%s\"data->in_files[0] %s", data->cmd, data->in_files[0]);
		// if (data->in_files[0] != NULL)
		// {
		// 	open_infiles(data);
		// }
		// else
			dup2(pipes[i - 1][PIPE_OUTPUT], STDIN_FILENO);
		close(pipes[i - 1][PIPE_OUTPUT]);
				// printf("changing the standard input of child %d to be ouput of pipe %d then close it\n", i, i - 1);
	}
	if (i != length - 1) // chande the output to be the input of the next cmd exept if this is not the last cmd
	{
		// if (data->out_files[0] != NULL)
		// 	open_outfiles(data);
		// else
			dup2(pipes[i][PIPE_INPUT], STDOUT_FILENO);
		close(pipes[i][PIPE_INPUT]);
	}
	if (data->files != NULL)
		handle_files(data->files, 0);
}
