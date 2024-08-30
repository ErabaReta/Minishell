/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:07:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/30 00:33:07 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// it splits str int 2d char pointer by '=' ir '+' , you find variable in indice 0 and value in indice 1 , if there is no value it puts NULL instead
t_env *slice_var_value(char *str)
{
	int	i;
	int	count;
	// char	**var_and_value;
	char *var;
	char *value;
	int	j;

	i = 0;
	count = 0;
	// var_and_value = (char **)malloc(sizeof(char *) * 2);
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
	/////////////////////////////
	if (str[i] == '=')
		i++;
	else if (str[i] == '+')
		i+=2;
	else if (str[i] == '\0')
	{
		value = NULL;
		return (env_new_node(var, value));
	}
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
void	env_lst_addback( t_env *new)
{
	t_env	*last_node;
	t_spec	*svars = get_specials();

	if (svars->env == NULL)
	{
		svars->env = new;
		return ;
	}
	last_node = env_lstlast(svars->env);
	last_node->next = new;
}
// creates new node of the var and its value, it dosnt create a copy of the string but directly assinging
t_env	*env_new_node(char *var, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->var = var; // there is directly assinging here not strduped !
	new->value = value; //
	new->next = NULL;
	return (new);
}

// turns a 2D chars into linked list
void	env_table_to_list(char **table)
{
	int	i;
	t_env	*tmp;
	// t_spec	*svars = get_specials();
	// t_env	*head;
	// char **splitted_var;

	i = 0;
	// head = svars->env;
	while (table[i] != NULL)
	{
		tmp = slice_var_value(table[i]); // if slice_var_value controled by gc, strdup it instead
		// tmp = env_new_node(ft_strdup(splitted_var[0]), ft_strdup(splitted_var[1]));
		env_lst_addback(tmp);
		// free(splitted_var[0]);
		// free(splitted_var[1]);
		// free(splitted_var);
		i++;
	}
	// return (head);
}
char *env_join_var_value(char *var, char *value)
{
	char *var_value;
	int	i;
	int	j;

	var_value = (char *)mallocate(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));//////////
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
char	**env_list_to_table()
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
		if (tmp->value != NULL)
			count++;
		tmp = tmp->next;
	}
	table = (char **)mallocate(sizeof(char *) * (count + 1));///////////
	tmp = svar->env;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
		{
			table[i] = env_join_var_value(tmp->var, tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	table[i] = NULL;
	return (table);
}
// returns the node that have the same variavle name, NULL if theres none
t_env	*env_search(char *var)
{
	t_spec *svar = get_specials();
	t_env	*tmp;

	tmp = svar->env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
