/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_var_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:50:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 22:52:00 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*slice_var(char *str, int *i)
{
	char	*var;
	int		count;
	int		j;

	count = 0;
	while (str[*i] != '\0' && str[*i] != '+' && str[*i] != '=')
	{
		count++;
		*i += 1;
	}
	var = (char *)malloc(sizeof(char) * (count + 1));
	j = 0;
	while (j < count)
	{
		var[j] = str[j];
		j++;
	}
	var[j] = '\0';
	return (var);
}

static char	*slice_value(char *str, int i)
{
	int		count;
	char	*value;
	int		j;

	count = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	value = (char *)malloc(sizeof(char) * (count + 1));
	j = -1;
	while (++j < count)
		value[j] = str[(i++) - count];
	value[j] = '\0';
	return (value);
}

/*it splits str int 2d char pointer by '=' ir '+' ,
	you find variable in indice 0 and value in indice 1 ,
	if there is no value it puts NULL instead*/
t_env	*slice_var_value(char *str)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	var = slice_var(str, &i);
	if (str[i] == '=')
		i++;
	else if (str[i] == '+')
		i += 2;
	else if (str[i] == '\0')
		return (env_new_node(var, NULL));
	value = slice_value(str, i);
	return (env_new_node(var, value));
}
