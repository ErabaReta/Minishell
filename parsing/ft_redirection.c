/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:23:31 by ayechcha          #+#    #+#             */
/*   Updated: 2024/07/31 21:23:31 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	red_checker(char **reds, int *i, t_data *data, int *passed)
{
	if (is_red(reds, data->args[*i]))
	{
		*passed = 1;
		if (data->args[*i + 1] && !is_red(reds, data->args[*i + 1]))
		{
			data->files = add_last(&data->files,
					make_new(data->args[*i], data->args[*i + 1]));
			*i = *i + 2;
		}
		else
		{
			data->files = add_last(&data->files,
					make_new(data->args[*i], NULL));
			*i = *i + 1;
		}
	}
}

void	redirection(t_data *data)
{
	int		i;
	int		passed;
	char	**reds;
	char	**cmds;

	reds = ft_split("< << > >>", ' ');
	passed = -1;
	while (data)
	{
		i = 0;
		cmds = NULL;
		while (data->args && data->args[i])
		{
			red_checker(reds, &i, data, &passed);
			if (passed == -1)
			{
				cmds = ft_tablejoin(cmds, data->args[i]);
				i++;
			}
			passed = -1;
		}
		data->args = ft_tabledup(cmds);
		data = data->next;
	}
}

void	her_writer(char *str, int tmp_file[2], int exp)
{
	int		i;
	char	*res;

	res = ft_strdup("");
	i = 0;
	if (exp == 1)
	{
		while (str[i])
			var_to_val(str, &i, &res, 0);
		write(tmp_file[PIPE_INPUT], res, ft_strlen(res));
	}
	else
		write(tmp_file[PIPE_INPUT], str, ft_strlen(str));
}

void	openchildherdoc(int tmp_file[2], char	*limiter, int exp)
{
	char	*str;
	char	*res;
	int		i;

	setup_signal_handler(0, sighandler, SIG_IGN);
	while (1)
	{
		str = readline("> ");
		i = 0;
		res = ft_strdup("");
		if (str == NULL || !ft_strncmp(limiter, str, ft_strlen(limiter) + 1))
		{
			if (str == NULL)
				print_err("warning: here-document delimited by end-of-file\n");
			break ;
		}
		her_writer(str, tmp_file, exp);
		write(tmp_file[PIPE_INPUT], "\n", 1);
		free(str);
	}
	free(str);
	exiter(0);
}

int	open_heredoc(char *limiter)
{
	int		tmp_file[2];
	int		exp;
	int		child_pid;
	int		status;
	t_spec	*svars;

	exp = 1;
	status = 0;
	svars = get_specials();
	safer_pipe(tmp_file);
	if (ft_strchr(limiter, '\"', NULL) || ft_strchr(limiter, '\'', NULL))
		limiter = quotes_remove(limiter, &exp);
	child_pid = safer_fork();
	if (child_pid == 0)
		openchildherdoc(tmp_file, limiter, exp);
	setup_signal_handler(1, SIG_DFL, SIG_IGN);
	waitpid(child_pid, &status, 0);
	svars->exit_status = status >> 8;
	ft_close(tmp_file[PIPE_INPUT]);
	if (svars->exit_status == 130 || svars->exit_status == 131)
		return (-1);
	return (tmp_file[PIPE_OUTPUT]);
}
