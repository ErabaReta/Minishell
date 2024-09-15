/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:50:47 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 22:32:23 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pwd_oldpwd(void)
{
	get_specials()->pwd = getcwd(NULL, 0);
	if (get_specials()->pwd == NULL)
		print_3_err("minishell: error retrieving current directory: ",
			"getcwd: cannot access parent directories",
			"No such file or directory", -1);
	else if (env_search("PWD") == NULL)
		env_lst_addback(env_new_node(ft_strdup2("PWD"),
				ft_strdup2(get_specials()->pwd)));
	else
	{
		free(env_search("PWD")->value);
		env_search("PWD")->value = ft_strdup2(get_specials()->pwd);
	}
	if (env_search("OLDPWD") == NULL)
		env_lst_addback(env_new_node(ft_strdup2("OLDPWD"), NULL));
}

void	init_shlvl(void)
{
	int		new_shlvl;

	if (env_search("SHLVL") == NULL)
		env_lst_addback(env_new_node(ft_strdup2("SHLVL"), ft_strdup2("1")));
	else
	{
		new_shlvl = ft_atoi(env_search("SHLVL")->value);
		if (new_shlvl <= 0)
			new_shlvl = 0;
		if (new_shlvl >= 999)
		{
			print_err("minishell: warning: shell level (");
			print_err(ft_itoa(new_shlvl + 1, 0));
			print_err(") too high, resetting to 1\n");
			new_shlvl = 0;
		}
		free(env_search("SHLVL")->value);
		env_search("SHLVL")->value = ft_itoa(new_shlvl + 1, 1);
	}
}

void	env_table_to_list(char **table)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (table[i] != NULL)
	{
		tmp = slice_var_value(table[i]);
		env_lst_addback(tmp);
		i++;
	}
}
