/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:47:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/02 18:06:58 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	is_dir(char *path)
{
	struct stat buff;
	
	stat(path, &buff);
	// printf("path =\'%s\'   , buf ==>%o\n", path, buff.st_mode);
	if (buff.st_mode <= 0 || access(path, F_OK) != 0)
		return (-1);
	if (buff.st_mode > 20000)// TODO check the right number
		return (0);
	return (1);
}

//checks relative path of cmd (existence and permissions)
char	*check_relative_path( char *file)
{
	char	*relative_path ;

	if (file[0] == '/')
		relative_path = file;
	else
		relative_path = ft_strnjoin("./", file, 0);
	if (access(relative_path, F_OK) == 0)
	{
		if (is_dir(relative_path))
		{
			print_err("minishell: ");
			print_err(file);
			print_err(": Is a directory\n");
			exiter(126);
		}
		if (access(relative_path, X_OK) == 0)// success
			return (relative_path);
		else
		{
			print_err("Minishell: ");
			print_err(file);
			print_err(": permission denied: \n");
			exiter(126);
		}
	}
	else
	{
		print_err("minishell: ");
		print_err(file);
		print_err(": No such file or directory\n");
		exiter(127);
	}
	return (NULL);
}
//checks if the cmd exist in any path the are in the enveriment (env)
char	*check_paths(char *cmd)
{
	int	i;
	char **paths;
	char *tmp_path;
	i = 0;
	t_env *tmp = env_search("PATH");
	if (tmp == NULL || tmp->value == NULL || tmp->value[0] == '\0')
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
			if (is_dir(tmp_path))
			{
				print_err("minishell: ");
				print_err(tmp_path);
				print_err(": Is a directory\n");
				exiter(126);
			}
			if (access(tmp_path, X_OK) == 0)
				return tmp_path;
			else
			{
				// printf("minishell: permission denied: %s\n", cmd);
				print_err("Minishell: ");
				print_err(cmd);
				print_err(": Permission denied\n");
				ft_free(tmp_path);
				exiter(126);
			}
		}
		i++;
		ft_free(tmp_path);
	}
	// printf("Minishell: command not found: %s\n", cmd);
	print_err("Minishell: command not found: ");
	print_err(cmd);
	print_err("\n");
	exiter(127);
	return (NULL);
}
