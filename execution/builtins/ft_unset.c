/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:40:21 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/04 19:30:11 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_data *data, t_env **env)
{
	int	i;
	t_env	*tmp;

	i = 1;
	tmp = *env;
	while (data->args[i] != NULL)
	{
		tmp = env_search(*env, data->args[i]);
		if (tmp != NULL)
		{
			tmp->var = "Deleted_var";
			tmp->value = "DELETED_value";
		}
		i++;
	}
	
}
