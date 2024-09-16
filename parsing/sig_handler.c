/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:35:33 by ayechcha          #+#    #+#             */
/*   Updated: 2024/09/08 14:35:33 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(char **reds, char *file)
{
	int	i;

	i = 0;
	while (file && reds[i])
	{
		if (ft_strncmp(file, reds[i], 3) == 0)
			return (1);
		else
			i++;
	}
	return (0);
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
	safer_signal(sig, sighandler);
}

void	setup_signal_handler(int p, void (*sig_h)(int), void (*sig_ign)(int))
{
	if (p == 0)
	{
		safer_signal(SIGINT, sig_h);
		safer_signal(SIGQUIT, sig_ign);
	}
	else if (p == 1)
	{
		safer_signal(SIGINT, sig_ign);
		safer_signal(SIGQUIT, sig_ign);
	}
}

void	set_last_arg(t_data *data)
{
	int		i;
	t_env	*env_node;

	i = 0;
	if (data && data->args && data->next == NULL)
	{
		while (data->args[i] && data->args[i + 1])
			i++;
		env_node = env_search("_");
		if (env_node == NULL)
			env_lst_addback(env_new_node(ft_strdup2("_"),
					last_arg(data->args[i])));
		else
		{
			free(env_search("_")->value);
			env_search("_")->value = last_arg(data->args[i]);
		}
	}
}
