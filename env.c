/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:07:57 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/04 11:46:53 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **slice_var_value(char *str)
{
	int	i;
	int	count;
	char	**var_and_value;
	int	j;

	i = 0;
	var_and_value = (char **)malloc(sizeof(char *) * 2);
	while (str[i] != '\0' && (str[i] != '=' || (str[i] != '+' && str[i] != '=')))
	{
		count++;
		i++;
	}
	var_and_value[0] = (char *)malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j < count)
	{
		var_and_value[0][j] = str[j];
		j++;
	}
	var_and_value[0][j] = '\0';
	/////////////////////////////
	if (str[i] != '=')
		i++;
	else if (str[i] != '+' && str[i] != '=')
		i+=2;
	else if (str[i] == '\0')
	{
		var_and_value[1] = NULL;
		return (var_and_value);
	}
	count = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	var_and_value[1] = (char *)malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j < count)
	{
		var_and_value[1][j] = str[j];
		j++;
	}
	var_and_value[1][j] = '\0';
	return (var_and_value);
}

t_env	*env_lstlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	if (env->next == NULL)
		return (env);
	return (ft_lstlast(env->next));
}

void	env_lst_addback(t_env **env, t_env *new)
{
	t_env	*last_node;

	if (env == NULL)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	last_node = env_lstlast(*env);
	last_node->next = new;
}

t_env	*env_new_node(char *var, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->var = var; // there is directly assinging here not strduped !
	new->value = value; //
	new->next = NULL;
	return (new);
}

t_env	*env_table_to_list(char **table)
{
	int	i;
	t_env	*tmp;
	t_env	*head;
	char **splitted_var;

	i = 0;
	head = NULL;
	while (table[i] != NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		splitted_var = slice_var_value(table[i]); // if slice_var_value controled by gc, strdup it instead
		tmp = env_new_node(splitted_var[0], splitted_var[1]);
		env_add_back(&head, tmp);
		i++;
	}
	return (head);
}

char	**env_list_to_table(t_env *head)
{
	int	count;
	t_env	*tmp;
	char	**table;
	int		i;

	tmp = head;
	while (tmp != NULL )
	{
		if (tmp->value != NULL)
			count++;
		tmp = tmp->next;
	}
	table = (char **)malloc(sizeof(char *) * (count + 1));
	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
		{
			table[i] = ft_strnjoin(ft_strnjoin(tmp->var, "=", 0), tmp->value, 0);
		}
		tmp = tmp->next;
		i++;
	}
	table[i] == NULL;
	return (table);
}

t_env	*env_search(t_env *env, char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var) + 1) == 0)
			return (tmp);
		tmp->next;
	}
	return (NULL);
}