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
			data->in_files = add_last(&data->in_files,
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

void	sighandler()
{
	write(1, "\n", 1);
	printf("H9\n");
	rl_redisplay();
	exit(0);
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
	struct sigaction	sa;
	// t_env	*env_list;

	// env_list = env_table_to_list(env);
	exp = 1;
	if (pipe(tmp_file) == -1 )
			printf("error : cant create pipe in here docement\n");
	if (limiter[0] == '\"' || limiter[0] == '\'')
	{
		exp = 0;
		limiter = quotes_remove(limiter);
	}
	child_pid = fork();
	if (child_pid != 0)
		is_herdoc(child_pid);
	if (child_pid == 0)
	{
		sa.sa_handler = sighandler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
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
		exit(0);
	}
	else
		wait(&status);
    int exit_status = (status & 0xff00) >> 8;
	exit_status += 34;
    printf("Exit status of the child was %d\n", exit_status);
	printf("exit status = %d\n", status);
	is_herdoc(0);
	// if (exit_status == 130)
		// looper(&env_list);
	close(tmp_file[PIPE_INPUT]); // ?
	return (tmp_file[PIPE_OUTPUT]);
}
