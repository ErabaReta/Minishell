/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:19:43 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/16 00:15:58 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_pwd_oldpwd(char *buff)
{
	if (env_search("OLDPWD") != NULL)
	{
		free(env_search("OLDPWD")->value);
		if (env_search("PWD") == NULL)
			env_search("OLDPWD")->value = ft_strdup2(buff);
		else if (env_search("PWD")->value == NULL)
			env_search("OLDPWD")->value = ft_strdup2("");
		else
			env_search("OLDPWD")->value = ft_strdup2(env_search("PWD")->value);
	}
	if (env_search("PWD") != NULL)
	{
		free(env_search("PWD")->value);
		env_search("PWD")->value = getcwd(NULL, 0);
	}
	free(get_specials()->pwd);
	free(buff);
	get_specials()->pwd = getcwd(NULL, 0);
	return (0);
}

int	chdir_to_home(void)
{
	char	*buff;

	if (env_search("HOME") == NULL || env_search("HOME")->value == NULL)
		return (print_err("minishell: cd: HOME not set\n") + 1);
	buff = getcwd(NULL, 0);
	if (buff == NULL && chdir(env_search("HOME")->value) == -1)
	{
		print_3_err("minishell: cd: ", env_search("HOME")->value,
			": No such file or directory\n", -1);
		return (1);
	}
	else if (env_search("HOME")->value[0] != '\0'
		&& chdir(env_search("HOME")->value) == -1)
	{
		free(buff);
		print_err("minishell: cd: ");
		perror(env_search("HOME")->value);
		return (1);
	}
	return (update_pwd_oldpwd(buff));
}

int	ft_cd(t_data *data)
{
	char	*buff;

	if (data->args[1] == NULL)
		return (chdir_to_home());
	else if (data->args[2] != NULL)
		return (print_err("minishell: cd: too many arguments\n") + 1);
	else
	{
		buff = getcwd(NULL, 0);
		if (buff == NULL && chdir(data->args[1]) == -1)
		{
			print_3_err("minishell: cd: ", data->args[1],
				": No such file or directory\n", -1);
			return (1);
		}
		if (data->args[1][0] != '\0' && chdir(data->args[1]) == -1)
		{
			free(buff);
			print_err("minishell: cd: ");
			perror(data->args[1]);
			return (1);
		}
		return (update_pwd_oldpwd(buff));
	}
}
