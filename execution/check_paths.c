/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:47:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/04 19:21:01 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//checks relative path of cmd (existence and permissions)
char	*check_relative_path( char *file)
{	
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == 0)
		{
			return (file);
		}
		else
		{
			printf("Minishell: permission denied: %s\n", file);
			return (NULL);
		}
	}
	else
	{
		printf("Minishell: command not found: %s\n", file);
		return (NULL);
	}
}
//checks if the cmd exist in any path the are in the enveriment (env)
char	*check_paths(char **env, char *cmd)
{
	int	i;
	char **paths;
	char *tmp_path;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		printf("Minishell: command not found: %s\n", cmd);
		return (NULL);
	}
	paths = ft_split(&(env[i][5]), ':');
	i = 0;
	while (paths[i] != NULL)
	{
		tmp_path = ft_strnjoin(ft_strnjoin(paths[i], "/", 0), cmd, 0);//TODO remove leak here
		// printf("%s\n", tmp_path);
		if (access(tmp_path, F_OK) == 0)
		{
			if (access(tmp_path, X_OK) == 0)
				return tmp_path;
			else
			{
				printf("minishell: permission denied: %s\n", cmd);
				//TODO freee <----------------------
				free(tmp_path);
				return (NULL);
			}
		}
		i++;
		free(tmp_path);
	}
	printf("Minishell: command not found: %s\n", cmd);
	return (NULL);
}
