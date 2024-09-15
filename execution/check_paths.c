/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:47:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 23:40:08 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dir(char *path)
{
	struct stat	buff;

	stat(path, &buff);
	if (buff.st_mode <= 0 || access(path, F_OK) != 0)
		return (-1);
	if (buff.st_mode > 040777 || buff.st_mode < 040000)
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
			print_3_err("minishell: ", file, ": Is a directory\n", 126);
		if (access(relative_path, X_OK) == 0)
			return (relative_path);
		else
			print_3_err("minishell: ", file, ": permission denied: \n", 126);
	}
	else
		print_3_err("minishell: ", file, ": No such file or directory\n", 127);
	return (NULL);
}

char	*check_paths(char *cmd)
{
	int		i;
	char	**paths;
	char	*tmp_path;

	if (env_search("PATH") == NULL || env_search("PATH")->value == NULL
		|| env_search("PATH")->value[0] == '\0')
		return (check_relative_path(cmd));
	paths = ft_split(env_search("PATH")->value, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		tmp_path = ft_strnjoin(ft_strnjoin(paths[i], "/", 0), cmd, 0);
		if (access(tmp_path, F_OK) == 0)
		{
			if (is_dir(tmp_path))
				print_3_err("minishell: ", tmp_path, ": Is a directory\n", 126);
			if (access(tmp_path, X_OK) == 0)
				return (tmp_path);
			else
				print_3_err("minishell: ", cmd, ": Permission denied\n", 126);
		}
		ft_free(tmp_path);
	}
	print_3_err(cmd, ": command not found", "\n", 127);
	return (NULL);
}
