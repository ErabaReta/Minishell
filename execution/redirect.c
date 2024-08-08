/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:02:27 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/07 15:34:25 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_heredoc(char *limiter, char **env)
{
	char	*res;
	int	tmp_file[2];
	int	i;
	int	exp;
	char *str;

	exp = 1;
	if (pipe(tmp_file) == -1 )
			printf("error : cant create pipe in here docement\n");
	if (limiter[0] == '\"' || limiter[0] == '\'')
	{
		exp = 0;
		limiter = quotes_remove(limiter);
	}
	while (1)
	{
		str = readline("HereDoc > ");
		i = 0;
		res = ft_strdup("");
		if (str == NULL || !ft_strncmp(limiter, str, ft_strlen(limiter)))
			break ;
		if (exp == 1)
		{
			while (str[i])
				var_to_val(str, &i, &res, env);
			write(tmp_file[PIPE_INPUT], res, ft_strlen(res));
			write(tmp_file[PIPE_INPUT], "\n", 1);
		}
		else
		{
			write(tmp_file[PIPE_INPUT], str, ft_strlen(str));
			write(tmp_file[PIPE_INPUT], "\n", 1);
		}
	}
	close(tmp_file[PIPE_INPUT]); // ?
	return (tmp_file[PIPE_OUTPUT]);
}

//opens the file after checking it existence and its permission then redirect the standard intput to it
void	open_infiles(t_data *data)
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
		else if (access(tmp->file, F_OK) == 0) // it exist
		{
			if (access(tmp->file, W_OK) == 0)// can be writen to it
			{
				fd = open(tmp->file, O_RDONLY);//TODO protect failing
				if (fd < 0)
				{
					printf("minishell: %s: failed to open file\n", tmp->file);//TODO custume ERR here
					exiter(data, 1);
				}
			}
			else
			{
				printf("Minishell: permission denied: %s\n", tmp->file);
				exiter(data, 1);
			}
			tmp = tmp->next;
		}
		else
		{
			fd = open(tmp->file, O_RDONLY);//TODO protect failing
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n",tmp->file);//TODO custume ERR here
				exiter(data, 1);
			}
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->next != NULL) // ?
			close(fd);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

//opens the file after checking it existence and its permission then redirect the standard output to it
void	open_outfiles(t_data *data)
{
	int	fd;
	// int	i;
	t_files_list *tmp;

	// i = 0;
	tmp = data->out_files;
	while (tmp != NULL)
	{
		if (access(tmp->file, F_OK) == 0) // it exist
		{
			if (access(tmp->file, W_OK) == 0)// can be writen to it
			{
				if (ft_strncmp(tmp->redirection, ">", 2) == 0)
					fd = open(tmp->file, O_WRONLY | O_TRUNC);// TODO protect failing
				else
					fd = open(tmp->file, O_WRONLY | O_APPEND);// TODO protect failing
				if (fd < 0)
				{
					printf("minishell: %s: failed to open file\n", tmp->file);//TODO custume ERR here
					exiter(data, 1);
				}
			}
			else
			{
				printf("Minishell: permission denied: %s\n", tmp->file);
				exiter(data, 1);
			}
			tmp = tmp->next;
		}
		else
		{
			if (ft_strncmp(tmp->redirection, ">", 2) == 0)
				fd = open(tmp->file, O_WRONLY | O_TRUNC | O_CREAT, 644);// TODO  protect failing
			else
				fd = open(tmp->file, O_WRONLY | O_APPEND | O_CREAT, 644);// TODO  protect failing	
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n",tmp->file);//TODO custume ERR here
				exiter(data, 1);
			}
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->next != NULL)
			close(fd);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

// closing all the not needed pipes and redirect the needed ones
void	piping(t_data *data, int **pipes, int length, int i)
{
	int j = 0;

	while (j < length - 1) // closing all the not needed pipes
	{
		if (j != i ) 
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
