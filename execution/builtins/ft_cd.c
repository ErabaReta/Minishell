/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:19:43 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/02 23:43:08 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_cd(t_data *data)
{
	t_env	*tmp;
	char *buff;
	t_spec	*svars = get_specials();

	if (data->args[1] == NULL)
	{
		// go home by $HOME
		tmp = env_search("HOME");
		if (tmp == NULL || tmp->value == NULL)
		{
			// printf("minishell: cd: HOME not set\n");
			print_err("minishell: cd: HOME not set\n");
			return (1);
		}
		buff = getcwd(NULL, 0);//
		if (buff == NULL && chdir(tmp->value) == -1)
		{
			print_err("minishell: cd: ");
			print_err(tmp->value);
			print_err(": No such file or directory\n");
			return (1);
		}
		else if (tmp->value[0] != '\0' && chdir(tmp->value) == -1)
		{
			free(buff);
			print_err("minishell: cd: ");
			perror(tmp->value);
			return (1);
		}
		if (env_search("OLDPWD") != NULL)
		{
			free(env_search("OLDPWD")->value);
			if (env_search("PWD") == NULL)
				env_search("OLDPWD")->value = ft_strdup2(buff);
			if ( env_search("PWD")->value == NULL)
				env_search("OLDPWD")->value = ft_strdup2("");
			else
				env_search("OLDPWD")->value = ft_strdup2(env_search("PWD")->value);
		}
		if (env_search("PWD") != NULL)
		{
			free(env_search("PWD")->value);
			env_search("PWD")->value = getcwd(NULL, 0);
		}
		free(svars->pwd);
		free(buff);
		svars->pwd = getcwd(NULL, 0);// updated pwd
		return (0);
	}
	else if (data->args[2] != NULL)
	{
		// err cd takes only one arg
		print_err("minishell: cd: too many arguments\n");
			return (1);
	}
	else
	{
		// go to path
		buff = getcwd(NULL, 0);// current pwd
		if (buff == NULL && chdir(data->args[1]) == -1)
		{
			print_err("minishell: cd: ");
			print_err(data->args[1]);
			print_err(": No such file or directory\n");
			return (1);
		}
		if (data->args[1][0] != '\0' && chdir(data->args[1]) == -1)
		{
			free(buff);
			print_err("minishell: cd: ");
			perror(data->args[1]);
			return (1);
		}
		// tmp = env_search("PWD");
		if (env_search("OLDPWD") != NULL)
		{
			free(env_search("OLDPWD")->value);
			if (env_search("PWD") == NULL)
				env_search("OLDPWD")->value = ft_strdup2(buff);
			if ( env_search("PWD")->value == NULL)
				env_search("OLDPWD")->value = ft_strdup2("");
			else
				env_search("OLDPWD")->value = ft_strdup2(env_search("PWD")->value);
		}
		if (env_search("PWD") != NULL)
		{
			free(env_search("PWD")->value);
			env_search("PWD")->value = getcwd(NULL, 0);
		}
		free(svars->pwd);
		free(buff);
		svars->pwd = getcwd(NULL, 0);// updated pwd
		return (0);
	}
}
