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

void	setup_signal_handler(int p, void (*sig_h)(int), void (*sig_ign)(int))
{
	if (p == 0)
	{
		signal(SIGINT, sig_h);
		signal(SIGQUIT, sig_ign);
	}
	else if (p == 1)
	{
		signal(SIGINT, sig_ign);
		signal(SIGQUIT, sig_ign);
	}
}

void	sig_exit(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
}
