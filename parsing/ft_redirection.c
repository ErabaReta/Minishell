/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:23:31 by ayechcha          #+#    #+#             */
/*   Updated: 2024/07/31 21:23:31 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	red_checker(char **reds, int *i, t_data *data, int *passed, char **env)
{
	int	j;

	j = 0;
	while (reds[j])
	{
		if (ft_strncmp(data->args[*i], reds[j], 2) == 0)
		{
			*passed = 1;
			data->in_files = add_last(&data->in_files,
					make_new(data->args[*i], data->args[*i + 1], env));
			*i = *i + 1;
		}
		j++;
	}
}

void	redirection(t_data *data, char **env)
{
	int		i;
	int		passed;
	char	**reds_in;
	char	**reds_out;
	char	**cmds;

	reds_in = ft_split("< <<", ' ');
	reds_out = ft_split("> >>", ' ');
	passed = -1;
	while (data)
	{
		i = 0;
		cmds = NULL;
		while (data->args && data->args[i])
		{
			red_checker(reds_in, &i, data, &passed, env);
			red_checker(reds_out, &i, data, &passed, env);
			if (passed == -1)
				cmds = ft_tablejoin(cmds, data->args[i]);
			passed = -1;
			i++;
		}
		data->args = ft_tabledup(cmds);
		data = data->next;
	}
}
