/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:02:31 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 20:13:50 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandler_exev(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		printf("quit (core dumped)\n");
	}
	safer_signal(sig, sighandler_exev);
}

// void	sig_exit_exev(int sig) // TODO useless??
// {
// 	t_spec	*svars;

// 	svars = get_specials();
// 	svars->exit_status = 128 + sig;
// 	// safer_signal(sig, sig_exit_exev);
// }
