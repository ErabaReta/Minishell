/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:40:21 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/09 20:48:45 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_data *data, char ***env)
{
	int	i;
	int	len;
	int	j;
	char	**new_env;

	i = 0;
	len = ft_strlen(data->args[1]);
	while ((*env)[i] != NULL)
	{
		if (strncmp((*env)[i], data->args[1], len) == 0)
		{
			j = 0;
			new_env = (char **)malloc(sizeof(char *) * (env_size(*env)));
			while (j < i)
			{
				new_env[j] = ft_strdup((*env)[j]);
				free((*env)[j]);
				j++;
			}
			free((*env)[j]);
			i++;
			while ((*env)[i] != NULL)
			{
				new_env[j] = ft_strdup((*env)[i]);
				free((*env)[i]);
				i++;
				j++;
			}
			new_env[j] = NULL;
			free((*env));
			*env = new_env;
			break ;
		}
		i++;
	}
}
