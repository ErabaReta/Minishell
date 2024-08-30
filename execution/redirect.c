/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:02:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/25 20:33:20 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//opens the file after checking it existence and its permission then redirect the standard intput to it
int	open_infiles(t_data *data)
{
	int	fd;
	// int	i;
	t_files_list *tmp;

	// i = 0;
	tmp = data->in_files;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->redirection, "<<", 3) == 0)
		{
			// fd = open_heredoc(tmp->file);
			fd = tmp->heredoc_fd;
			tmp = tmp->next;
		}
		else if (tmp->heredoc_fd == -1)
		{
			print_err("minishell: ambiguous redirect\n");
			return (1);
		}
		else if (access(tmp->file, F_OK) == 0) // it exist
		{
			if (is_dir(tmp->file))
			{
				print_err("minishell: ");
				print_err(tmp->file);
				print_err(": Is a directory\n");
				return (1);
			}
			if (access(tmp->file, W_OK) == 0)// can be writen to it
			{
				fd = open(tmp->file, O_RDONLY);//TODO protect failing
				if (fd < 0)
				{
					// printf("minishell: %s: failed to open file\n", tmp->file);//TODO custume ERR here
					print_err("minishell: ");
					print_err(tmp->file);
					print_err(": failed to open file\n");
					return (1);
				}
			}
			else
			{
				// printf("Minishell: permission denied: %s\n", tmp->file);
				print_err("minishell: permission denied: ");
				print_err(tmp->file);
				print_err("\n");
				return (1);
			}
			tmp = tmp->next;
		}
		else
		{
			fd = open(tmp->file, O_RDONLY);//TODO protect failing
			if (fd < 0)
			{
				// printf("minishell: %s: No such file or directory\n",tmp->file);//TODO custume ERR here
				print_err("minishell: ");
				print_err(tmp->file);
				print_err(": No such file or directory\n");
				return (1);
			}
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->next != NULL) // ?
			close(fd);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

//opens the file after checking it existence and its permission then redirect the standard output to it
int	open_outfiles(t_data *data)
{
	int	fd;
	t_files_list *tmp;
	tmp = data->out_files;
	
	while (tmp != NULL)
	{
		if (tmp->heredoc_fd == -1)
		{
			print_err("minishell: ambiguous redirect\n");
			return (1);
		}
		else if (access(tmp->file, F_OK) == 0) // it exist
		{
			if (is_dir(tmp->file))
			{
				print_err("minishell: ");
				print_err(tmp->file);
				print_err(": Is a directory\n");
				return (1);
			}
			if (access(tmp->file, W_OK) == 0)// can be writen to it
			{
				if (ft_strncmp(tmp->redirection, ">", 2) == 0)
					fd = open(tmp->file, O_WRONLY | O_TRUNC);// TODO protect failing
				else
					fd = open(tmp->file, O_WRONLY | O_APPEND);// TODO protect failing
				if (fd < 0)
				{
					// printf("minishell: %s: failed to open file\n", tmp->file);//TODO custume ERR here
					print_err("minishell: ");
					print_err(tmp->file);
					print_err(": failed to open file\n");
					return (1);
				}
			}
			else
			{
				// printf("Minishell: permission denied: %s\n", tmp->file);
				print_err("minishell: permission denied: ");
				print_err(tmp->file);
				print_err("\n");
				return (1);
			}
			tmp = tmp->next;
		}
		else
		{
			if (ft_strncmp(tmp->redirection, ">", 2) == 0)
				fd = open(tmp->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);// TODO  protect failing
			else
				fd = open(tmp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);// TODO  protect failing	
			if (fd < 0)
			{
				// printf("minishell: %s: No such file or directory\n",tmp->file);//TODO custume ERR here
				print_err("minishell: ");
				print_err(tmp->file);
				print_err(": No such file or directory\n");
				exiter(1);
			}
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->next != NULL)
			close(fd);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
	if (data->in_files != NULL)
		open_infiles(data);
	if (data->out_files != NULL)
	{
		open_outfiles(data);
	}
}
