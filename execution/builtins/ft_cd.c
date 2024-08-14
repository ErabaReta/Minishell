/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:19:43 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/14 14:32:21 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_cd(t_data *data)
{
	t_env	*tmp;

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
		if (is_dir(tmp->value) == -1)
		{
			print_err("minishell: cd: ");
			print_err(tmp->value);
			print_err(": No such file or directory\n");
			return (1);
		}
		else if (!is_dir(tmp->value))
		{
			print_err("minishell: cd: ");
			print_err(tmp->value);
			print_err(": Not a directory\n");
			return (1);
		}
		else if (access(tmp->value, X_OK) != 0)
		{
			print_err("minishell: cd: ");
			print_err(tmp->value);
			print_err(": Permission denied");
			return (1);
		}
		chdir(tmp->value);
		return (0);
	}
	else if (data->args[2] != NULL)
	{
		// err cd takes only one arg
		// printf("minishell: cd: too many arguments\n");
		print_err("minishell: cd: too many arguments\n");
			return (1);
	}
	else
	{
		// go to path
		int cases = is_dir(data->args[1]);
		
		if (cases == -1)
		{
			print_err("minishell: cd: ");
			print_err(data->args[1]);
			print_err(": No such file or directory\n");
			return (1);
		}
		else if (cases == 0)
		{
			print_err("minishell: cd: ");
			print_err(data->args[1]);
			print_err(": Not a directory\n");
			return (1);
		}
		else if (access(data->args[1], X_OK) != 0)
		{
			print_err("minishell: cd: ");
			print_err(data->args[1]);
			print_err(": Permission denied\n");
			return (1);
		}
		chdir(data->args[1]);
		return (0);
	}
}
