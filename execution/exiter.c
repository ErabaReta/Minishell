/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:07:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/14 09:58:48 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env()
{
	t_spec *svars;
	t_env *env;

	svars = get_specials();
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
	exit(code);
}
