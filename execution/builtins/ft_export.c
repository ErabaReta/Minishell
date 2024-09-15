/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:43:18 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 22:20:30 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_vars(void)
{
	t_env	*tmp;
	char	**vars;
	int		i;

	i = 0;
	vars = get_vars_sorted();
	while (vars[i] != NULL)
	{
		if (ft_strncmp(vars[i], "_", 2) != 0)
		{
			tmp = env_search(vars[i]);
			if (tmp->value == NULL)
				printf("declare -x %s\n", tmp->var);
			else
				printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		}
		i++;
	}
}

int	check_env_validity(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || str[0] == '+' || ft_isdigit(str[0]) || str[0] == '\0')
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

void	handle_var_value(t_env *var_and_value, t_env *tmp, int validity)
{
	if (var_and_value->value != NULL)
	{
		if (validity == 2 || validity == 0
			|| (validity == 1 && tmp->value == NULL))
		{
			free(tmp->value);
			tmp->value = var_and_value->value;
			free(var_and_value->var);
			free(var_and_value);
		}
		else if (validity == 1)
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

void	export_arg(char *arg, int *status)
{
	int		validity;
	t_env	*tmp;
	t_env	*var_and_value;

	validity = check_env_validity(arg);
	if (validity == -1)
	{
		print_3_err("minishell: export: `", arg,
			"': not a valid identifier\n", -1);
		*status = 1;
	}
	else if (ft_strncmp(arg, "_", 2) != 0)
	{
		var_and_value = slice_var_value(arg);
		tmp = env_search(var_and_value->var);
		if (tmp == NULL)
			env_lst_addback(var_and_value);
		else
			handle_var_value(var_and_value, tmp,
				validity);
	}
}

void	ft_export(t_data *data, int	*status)
{
	int		i;

	*status = 0;
	if (data->args[1] == NULL)
	{
		print_vars();
		return ;
	}
	i = 1;
	while (data->args[i] != NULL)
	{
		export_arg(data->args[i], status);
		i++;
	}
}
