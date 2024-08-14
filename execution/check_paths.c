/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:47:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/13 22:48:33 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dir(char *path)
{
	struct stat buff;
	
	stat(path, &buff);
	if (buff.st_mode > 20000)// TODO check the right number
		return (0);
	return (1);
}

//checks relative path of cmd (existence and permissions)
char	*check_relative_path( char *file)
{
	char	*relative_path = ft_strnjoin("./", file, 0);
	if (access(relative_path, F_OK) == 0)
	{
		if (access(relative_path, X_OK) == 0)
		{
			return (relative_path);
		}
		else
		{
			// printf("Minishell: permission denied: %s\n", file);
			print_err("Minishell: ");
			print_err(file);
			print_err(": permission denied: \n");
			exiter(126);
			return (NULL);
		}
	}
	else
	{
		// printf("Minishell: command not found: %s\n", file);
		print_err("minishell: command not found: ");
		print_err(file);
		print_err("\n");
		return (NULL);
	}
}
//checks if the cmd exist in any path the are in the enveriment (env)
char	*check_paths(char *cmd)
{
	int	i;
	char **paths;
	char *tmp_path;
	i = 0;
	t_env *tmp = env_search("PATH");
	if (tmp == NULL)
	{
		// check if it is in the dir
		return (check_relative_path(cmd));
	}
	paths = ft_split(tmp->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		tmp_path = ft_strnjoin(ft_strnjoin(paths[i], "/", 0), cmd, 0);
		// printf("%s\n", tmp_path);
		if (access(tmp_path, F_OK) == 0)
		{
			if (access(tmp_path, X_OK) == 0)
				return tmp_path;
			else
			{
				// printf("minishell: permission denied: %s\n", cmd);
				print_err("Minishell: permission denied: ");
				print_err(cmd);
				print_err("\n");
				ft_free(tmp_path);
				return (NULL);
			}
		}
		i++;
		ft_free(tmp_path);
	}
	// printf("Minishell: command not found: %s\n", cmd);
	print_err("Minishell: command not found: ");
	print_err(cmd);
	print_err("\n");
	return (NULL);
}
