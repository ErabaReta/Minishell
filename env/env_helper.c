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
