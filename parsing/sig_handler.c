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
	struct sigaction	sa;

	sa.sa_flags = 0;
	if (p == 0)
	{
		sa.sa_handler = sig_h;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIGINT, &sa, NULL) != 0)
			exiter(1);
		sa.sa_handler = sig_ign;
		if (sigaction(SIGQUIT, &sa, NULL) != 0)
			exiter(1);
	}
	else if (p == 1)
	{
		sa.sa_handler = sig_h;
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

void	sig_exit(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
}
