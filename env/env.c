/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:07:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 21:53:51 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_join_var_value(char *var, char *value)
{
	char	*var_value;
	int		i;
	int		j;

	var_value = (char *)mallocate(sizeof(char) * (ft_strlen(var)
				+ ft_strlen(value) + 2));
	i = 0;
	while (var[i] != '\0')
	{
		var_value[i] = var[i];
		i++;
	}
	var_value[i] = '=';
	i++;
	j = 0;
	while (value[j] != '\0')
	{
		var_value[i + j] = value[j];
		j++;
	}
	var_value[i + j] = '\0';
	return (var_value);
}

// turns a linked list into 2D chars NULL terminated
char	**env_list_to_table(void)
{
	t_env	*tmp;
	char	**table;
	int		i;

	tmp = get_specials()->env;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
			i++;
		tmp = tmp->next;
	}
	table = (char **)mallocate(sizeof(char *) * (i + 1));
	tmp = get_specials()->env;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
			table[i++] = env_join_var_value(tmp->var, tmp->value);
		tmp = tmp->next;
	}
	table[i] = NULL;
	return (table);
}

/*returns the node that have the same variavle name, NULL if theres none*/
t_env	*env_search(char *var)
{
	t_spec	*svar;
	t_env	*tmp;

	svar = get_specials();
	tmp = svar->env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_vars_sorted(void)
{
	int		count;
	t_env	*tmp;
	char	**table;
	int		i;

	tmp = get_specials()->env;
	count = 0;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	table = (char **)mallocate(sizeof(char *) * (count + 1));
	tmp = get_specials()->env;
	i = 0;
	while (tmp != NULL)
	{
		table[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	table[i] = NULL;
	sort_table(table, count);
	return (table);
}

void	append_value(t_env *env, char *value)
{
	char	*new_value;
	int		i;
	int		j;

	new_value = (char *)malloc(sizeof(char) * (ft_strlen(env->value)
				+ ft_strlen(value) + 1));
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
