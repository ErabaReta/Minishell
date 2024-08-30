/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:43:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/30 02:52:57 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_vars(char **vars, int lenght)
{
	int	i;
	int	j;
	int	k;
	char	*tmp;

	if (lenght <= 1)
		return ;
	i = 0;
	while (i < lenght - 1)
	{
		j = i + 1;
		while (j < lenght)
		{
			k = 0;
			while (vars[i][k] == vars[j][k])
				k++;
			if (vars[i][k] > vars[j][k])
			{
				tmp = vars[i];
				vars[i] = vars[j];
				vars[j] = tmp;
			}
			j++;
		}
		i++;
		
	}
}

char	**get_vars_sorted()
{
	int	count;
	t_env	*tmp;
	char	**table;
	int		i;

	t_spec *svar = get_specials();
	tmp = svar->env;
	count = 0;
	while (tmp != NULL )
	{
		count++;
		tmp = tmp->next;
	}
	table = (char **)mallocate(sizeof(char *) * (count + 1));///////////
	tmp = svar->env;
	i = 0;
	while (tmp != NULL)
	{
		table[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	table[i] = NULL;
	sort_vars(table, count);
	return (table);
}

void	print_vars()
{
	// t_spec	*svars = get_specials();
	t_env *tmp;
	char **vars = get_vars_sorted();
	int	i;
	
	i = 0;
	while (vars[i] != NULL)
	{
		tmp = env_search(vars[i]);
		if (tmp->value == NULL)
			printf("declare -x %s\n", tmp->var);
		else
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		i++;
	}
}

int	check_env_validity(char *str)
{
	int	i;
	// int	returned;

	i = 0;
	// returned = 2;
	if (str[0] == '=' || str[0] == '+')
		return (-1);
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

void	append_value(t_env	*env, char *value)
{
	char	*new_value;
	int	i;
	int	j;

	new_value = (char *)malloc(sizeof(char) * (ft_strlen(env->value) + ft_strlen(value) + 1));
	i = 0;
	while (env->value[i] != '\0')
	{
		new_value[i] = env->value[i];
		i++;
	}
	j = 0;
	while (value[j] != '\0')
	{
		new_value[i + j] = value[j];
		j++;
	}
	new_value[i + j] = '\0';
	free(env->value);
	free(value);
	env->value = new_value;
}

void	ft_export(t_data *data, int	*status)
{
	int	i;
	int	validity;
	t_env *var_and_value;
	t_env	*tmp;

	*status = 0;
	if (data->args[1] == NULL)
	{
		print_vars();
		return ;
	}
	i = 1;
	while (data->args[i] != NULL)
	{
		validity = check_env_validity(data->args[i]);
		if (validity == -1)// wrong var format
		{
			// printf("minishell: export: `%s': not a valid identifier\n", data->args[i]);
			print_err("minishell: export: `");
			print_err(data->args[i]);
			print_err("': not a valid identifier\n");
			i++;
			*status = 1;
			continue ;
		}
		else  // doesn't contain '=' || //contains '=' || // contains +=
		{
			var_and_value = slice_var_value(data->args[i]);
			tmp = env_search(var_and_value->var);
			if (tmp == NULL)
			{
				env_lst_addback(var_and_value);
			}
			else
			{
				if (var_and_value->value != NULL)
				{
					if (validity == 2 || validity == 0 || (validity == 1 && tmp->value == NULL))// doesn't contain '=' || //contains '='
					{
						free(tmp->value);
						tmp->value = var_and_value->value;
						free(var_and_value->var);
						free(var_and_value);
					}
					else if (validity == 1) // contains +=
					{
						append_value(tmp, var_and_value->value);
						free(var_and_value->var);
						free(var_and_value);
					}
				}
				else
				{
					free(var_and_value->value);
					free(var_and_value->var);
					free(var_and_value);
				}
			}
		}
		i++;
	}
}
