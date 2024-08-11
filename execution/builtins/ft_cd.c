/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:19:43 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/10 21:40:45 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_cd(t_data *data)
{
	t_env	*tmp;

	if (data->args[1] == NULL)
	{
		// go home by $HOME
		tmp = env_search("HOME");
		if (tmp == NULL)
		{
			// printf("minishell: cd: HOME not set\n");
			print_err("minishell: cd: HOME not set\n");
			return ;
		}
		chdir(tmp->value);
	}
	else if (data->args[2] != NULL)
	{
		// err cd takes only one arg
		// printf("minishell: cd: too many arguments\n");
		print_err("minishell: cd: too many arguments\n");
		return ;
	}
	else
	{
		// go to path
		chdir(data->args[1]);
	}
}
