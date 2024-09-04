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
	int	j;

	j = 0;
	while (reds[j])
	{
		if (ft_strncmp(data->args[*i], reds[j], 2) == 0)
		{
			*passed = 1;
			data->files = add_last(&data->files,
					make_new(data->args[*i], data->args[*i + 1]));
			*i = *i + 1;
		}
		j++;
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
				cmds = ft_tablejoin(cmds, data->args[i]);
			passed = -1;
			i++;
		}
		data->args = ft_tabledup(cmds);
		data = data->next;
	}
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		rl_on_new_line();
	}
	exiter(128 + sig);
}

void	sig_exit(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
}

void setup_signal_handler(int parent, void (*sig_handle)(int), void (*sig_ign)(int))
{
    struct sigaction sa;

	sa.sa_flags = 0;
	if (parent == 0)
	{
		sa.sa_handler = sig_handle;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) != 0)
			exiter(1);
		sa.sa_handler = sig_ign;
		if (sigaction(SIGQUIT, &sa, NULL) != 0)
			exiter(1);
	}
	else if (parent == 1)
	{
		sa.sa_handler = sig_handle;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIGCHLD, &sa, NULL) != 0)
			exiter(1);
		sa.sa_handler = sig_ign;
		if (sigaction(SIGINT, &sa, NULL) != 0)
			exiter(1);
		if (sigaction(SIGQUIT, &sa, NULL) != 0)
			exiter(1);
	}
}

void	openchildherdoc(int tmp_file[2], char	*limiter, int exp)
{
	char	*str;
	char	*res;
	int		i;

	setup_signal_handler(0, sighandler, SIG_IGN);
	while (1)
	{
		str = readline("HereDoc > ");
		i = 0;
		res = ft_strdup("");
		if (str == NULL || !ft_strncmp(limiter, str, ft_strlen(limiter)))
		{
			if (str == NULL)
				printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (exp == 1)
		{
			while (str[i])
				var_to_val(str, &i, &res);
			write(tmp_file[PIPE_INPUT], res, ft_strlen(res));
		}
		else
			write(tmp_file[PIPE_INPUT], str, ft_strlen(str));
		write(tmp_file[PIPE_INPUT], "\n", 1);
	}
	exiter(0);
}

int	open_heredoc(char *limiter)
{
	int	tmp_file[2];
	int	exp;
	int	child_pid;
	int	status;
	t_spec	*svars;

	exp = 1;
	status = 0;
	svars = get_specials();
	if (pipe(tmp_file) == -1 )
			printf("error : cant create pipe in here docement\n");
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '\"'))
	{
		exp = 0;
		limiter = quotes_remove(limiter);
	}
	child_pid = fork();
	if (child_pid == 0)
		openchildherdoc(tmp_file, limiter, exp);
	setup_signal_handler(1, SIG_DFL, SIG_IGN);
	waitpid(child_pid, &status, 0);
	svars->exit_status = status >> 8;
	close(tmp_file[PIPE_INPUT]); // ?
	if (svars->exit_status == 130 || svars->exit_status == 131)
	{
		close(tmp_file[PIPE_OUTPUT]); // ?
		return (-1);
	}
	return (tmp_file[PIPE_OUTPUT]);
}
