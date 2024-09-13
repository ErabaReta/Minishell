/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:07:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/13 19:36:53 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(void)
{
	t_spec	*svars;
	t_env	*env;

	svars = get_specials();
	free(svars->pwd);
	while (svars->env != NULL)
	{
		env = svars->env;
		svars->env = svars->env->next;
		free(env->var);
		free(env->value);
		free(env);
	}
}

void	exiter(int code)
{
	clean_pool();
	free_all_heap();
	free_env();
	// close(STDERR_FILENO);//////////// TODO remove this ugliness, it makes no sense
	// close(STDIN_FILENO);/////////////
	// close(STDOUT_FILENO);////////////
	exit(code);
}
