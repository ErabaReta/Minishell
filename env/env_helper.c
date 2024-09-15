/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:43:21 by ayechcha          #+#    #+#             */
/*   Updated: 2024/09/13 17:46:18 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*it splits str int 2d char pointer by '=' ir '+' ,
	you find variable in indice 0 and value in indice 1 ,
	if there is no value it puts NULL instead*/
t_env	*slice_var_value(char *str)
{
	int		i;
	int		count;
	char	*var;
	char	*value;
	int		j;

	i = 0;
	count = 0;
	while (str[i] != '\0' && str[i] != '+' && str[i] != '=')
	{
		count++;
		i++;
	}
	var = (char *)malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j < count)
	{
		var[j] = str[j];
		j++;
	}
	var[j] = '\0';
	if (str[i] == '=')
		i++;
	else if (str[i] == '+')
		i += 2;
	else if (str[i] == '\0')
		return (env_new_node(var, NULL));
	count = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	value = (char *)malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j < count)
	{
		value[j] = str[i - count];
		j++;
		i++;
	}
	value[j] = '\0';
	return (env_new_node(var, value));
}

// returns the last node of the list, NULL if empty or on error
t_env	*env_lstlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	if (env->next == NULL)
		return (env);
	return (env_lstlast(env->next));
}

// adds a variable to the end of the env
void	env_lst_addback(t_env *new)
{
	t_env	*last_node;
	t_spec	*svars;

	svars = get_specials();
	if (svars->env == NULL)
	{
		svars->env = new;
		return ;
	}
	last_node = env_lstlast(svars->env);
	last_node->next = new;
}

/*creates new node of the var and its value,
	it dosnt create a copy of the string but directly assinging*/
t_env	*env_new_node(char *var, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->var = var;
	new->value = value;
	new->next = NULL;
	return (new);
}

// turns a 2D chars into linked list
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
