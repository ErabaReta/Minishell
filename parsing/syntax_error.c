/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunter <hunter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:11 by hunter            #+#    #+#             */
/*   Updated: 2024/08/01 18:29:33 by hunter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*syntax_error(t_data *data)
{
	int		i;
	int		j;
	t_data	*curr;
	char	**reds;

	reds = ft_split("< << > >>", ' ');
	curr = data;
	while (curr)
	{
		if (curr->next != NULL)
		{
			if (curr->next->args[0] == NULL || curr->args[0] == NULL)
			{
				printf("syntax error near unexpected token `|'\n");
				return (NULL);
			}
		}
		curr = curr->next;
	}
	curr = data;
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			j = 0;
			while (reds[j])
			{
				if (ft_strncmp(curr->args[i], reds[j], 2) == 0 && curr->args[i + 1] == NULL)
				{
					printf("syntax error near unexpected token %s\n",
						curr->args[i]);
					return (NULL);
				}
				j++;
			}
			i++;
		}
		curr = curr->next;
	}
	return (data);
}
