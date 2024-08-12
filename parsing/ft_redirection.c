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

void	red_checker(char **reds, int *i, t_data *data, int *passed, char **env)
{
	int	j;

	j = 0;
	while (reds[j])
	{
		if (ft_strncmp(data->args[*i], reds[j], 2) == 0)
		{
			*passed = 1;
			if (reds[0][0] == '<')
				data->in_files = add_last(&data->in_files,
						make_new(data->args[*i], data->args[*i + 1], env));
			if (reds[0][0] == '>')
				data->out_files = add_last(&data->out_files,
						make_new(data->args[*i], data->args[*i + 1], env));
			*i = *i + 1;
		}
		j++;
	}
}

void	redirection(t_data *data, char **env)
{
	int		i;
	int		passed;
	char	**reds_in;
	char	**reds_out;
	char	**cmds;

	reds_in = ft_split("< <<", ' ');
	reds_out = ft_split("> >>", ' ');
	passed = -1;
	while (data)
	{
		i = 0;
		cmds = NULL;
		while (data->args && data->args[i])
		{
			red_checker(reds_in, &i, data, &passed, env);
			red_checker(reds_out, &i, data, &passed, env);
			if (passed == -1)
				cmds = ft_tablejoin(cmds, data->args[i]);
			passed = -1;
			i++;
		}
		data->args = ft_tabledup(cmds);
		data = data->next;
	}
}

int	is_herdoc(int pid)
{
	static	int	is;

	if (pid != -1)
		is = pid;
	return (is);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		rl_on_new_line();
	}
	exit(128 + sig);
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

	if (parent == 0)
	{
		sa.sa_handler = sig_handle;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIGINT, &sa, NULL) != 0)
			exit(0);
		sa.sa_handler = sig_ign;
		if (sigaction(SIGQUIT, &sa, NULL) != 0)
			exit(0);
	}
	else if (parent == 1)
	{
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = sig_handle;
		if (sigaction(SIGCHLD, &sa, NULL) != 0)
			exit(0);
		sa.sa_handler = sig_ign;
		if (sigaction(SIGINT, &sa, NULL) != 0)
			exit(0);
	}
}

int	open_heredoc(char *limiter, char **env)
{
	char	*res;
	int	tmp_file[2];
	int	i;
	int	exp;
	char *str;
	int	child_pid;
	int	status;
	t_spec	*svars;

	exp = 1;
	svars = get_specials();
	if (pipe(tmp_file) == -1 )
			printf("error : cant create pipe in here docement\n");
	if (limiter[0] == '\"' || limiter[0] == '\'')
	{
		exp = 0;
		limiter = quotes_remove(limiter);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
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
		exit(0);
	}
	else
	{
		setup_signal_handler(1, SIG_DFL, SIG_IGN);
		waitpid(child_pid, &status, 0);
	}
	svars->exit_status = status >> 8;
	is_herdoc(0);
	close(tmp_file[PIPE_INPUT]); // ?
	if (svars->exit_status == 130 || svars->exit_status == 131)
	{
		close(tmp_file[PIPE_OUTPUT]); // ?
		return (-1);
	}
	return (tmp_file[PIPE_OUTPUT]);
}
