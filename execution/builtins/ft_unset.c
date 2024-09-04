/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:40:21 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 22:42:23 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_env_node(t_env *tmp, char *arg)
{
	t_env	*to_delete;

	if (ft_strncmp(tmp->var, arg,
			ft_strlen(arg) + 1) == 0)
	{
		get_specials()->env = tmp->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp != NULL && tmp->next != NULL)
	{
		if (ft_strncmp(tmp->next->var, arg,
				ft_strlen(arg) + 1) == 0)
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
}

int	ft_unset(t_data *data)
{
	int		i;
	t_env	*tmp;

	i = -1;
	while (data->args[++i] != NULL)
	{
		tmp = get_specials()->env;
		if (tmp == NULL)
			break ;
		if (ft_strncmp("_", data->args[i], 2) == 0)
			continue ;
		del_env_node(tmp, data->args[i]);
	}
	return (0);
}
