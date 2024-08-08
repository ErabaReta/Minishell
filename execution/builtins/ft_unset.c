/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:40:21 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/08 14:08:08 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_data *data, t_env **env)
{
	int	i;
	t_env	*tmp;
	t_env	*to_delete;
	i = 1;
	while (data->args[i] != NULL)
	{
		tmp = *env;
		if (tmp == NULL)
			break ;
		if (ft_strncmp(tmp->var, data->args[i], ft_strlen(data->args[i]) + 1) == 0)
		{
			*env = tmp->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
			i++;
			continue ;
		}
		while (tmp != NULL && tmp->next != NULL)
		{
			if (ft_strncmp(tmp->next->var, data->args[i], ft_strlen(data->args[i]) + 1) == 0)
			{
				to_delete = tmp->next;
				tmp->next = tmp->next->next;
				free(to_delete->var);
				free(to_delete->value);
				free(to_delete);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	
}
