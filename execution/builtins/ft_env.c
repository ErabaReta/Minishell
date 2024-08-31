/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:38:47 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/31 19:31:27 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(char **env, int is_parent)
{
	int	i;
	int new_shlvl;
	
	if (!is_parent && env_search("SHLVL") == NULL)
		printf("SHLVL=0\n");
	i = 0;
	while (env != NULL && env[i] != NULL)
	{
		if (!is_parent && ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			new_shlvl = ft_atoi(&env[i][6]);
			if (new_shlvl <= 0)
				new_shlvl = 0;
			printf("SHLVL=%d\n", new_shlvl -1);
		}
		else
			printf("%s\n", env[i]);
		i++;
	}
}
