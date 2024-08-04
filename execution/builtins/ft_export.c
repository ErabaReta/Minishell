/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:43:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/04 17:39:07 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_vars(t_env *env)
{
	while (env != NULL)
	{
		if (env->value == NULL)
			printf("declare -x %s\n", env->var);
		else
			printf("declare -x %s=\"%s\"\n", env->var, env->value);
		env = env->next;
	}
}

int	check_env_validity(char *str)
{
	int	i;
	// int	returned;

	i = 0;
	// returned = 2;
	while (str[i] != '\0')
	{
		if (ft_strncmp(&str[i], "+=", 2) == 0)
			return (1);
		if (str[i] == '=')
			return (0);
		if (ft_isalnum(str[i]) != 1 && str[i] != '_')
			return (-1);
		i++;
	}
	return (2);
}

void	ft_export(t_data *data, t_env **env)
{
	int	i;
	int	validity;
	char	**var_and_value;
	t_env	*tmp;

	if (data->args[1] == NULL)
	{
		print_vars(*env);
		return ;
	}
	i = 1;
	while (data->args[i] != NULL)
	{
		validity = check_env_validity(data->args[i]);
		if (validity == -1)// wrong var format
		{
			printf("minishell: export: `%s': not a valid identifier\n", data->args[i]);
			i++;
			continue ;
		}
		else  // doesn't contain '=' || //contains '=' || // contains +=
		{
			var_and_value = slice_var_value(data->args[i]);
			tmp = env_search(*env, var_and_value[0]);
			if (tmp == NULL)
			{
				tmp = env_new_node(var_and_value[0], var_and_value[1]);
				env_lst_addback(env, tmp);
			}
			else
			{
				if (var_and_value[1] != NULL )
				{
					if (validity == 2 || validity == 0)// doesn't contain '=' || //contains '='
						tmp->value = var_and_value[1];
					else if (validity == 1) // contains +=
						tmp->value = ft_strnjoin(tmp->value, var_and_value[1], 0);
				}
			}
		}
		i++;
	}
}
