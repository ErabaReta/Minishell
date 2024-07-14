/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:43:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/09 20:56:45 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void	ft_export(t_data *data, char ***env)
{
	char	**new_env;
	char	**args;
	int	i;

	i = 0;
	args = ft_split(data->args[1], '=');
	while ((*env)[i] != NULL)
	{
		if (strncmp((*env)[i], args[0], ft_strlen(args[0])) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(data->args[1]);
			free(args[0]);
			free(args[1]);
			free(args);
			return ;
		}
		i++;
	}
	new_env = (char **)malloc(sizeof(char *) * (env_size(*env) + 2));
	i = 0;
	while ((*env)[i] != NULL)
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	free(*env);
	new_env[i] = ft_strdup(data->args[1]);
	free(args[0]);
	free(args[1]);
	free(args);
	new_env[++i] = NULL;
	*env = new_env;
}