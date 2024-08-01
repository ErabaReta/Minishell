/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunter <hunter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:15:57 by hunter            #+#    #+#             */
/*   Updated: 2024/08/01 18:15:57 by hunter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*catch_expnad(char *arg, char **env)
{
	int		i;
	int		end;
	char	*res;

	i = 0;
	end = 0;
	res = NULL;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			end = ++i;
			while (arg[end] != '\'' && arg[end])
				end++;
			res = ft_strnjoin(res, ft_substr(arg, i, end - i), 0);
			if (arg[end] == '\'')
				i = ++end;
		}
		else if (arg[i] == '\"')
		{
			i++;
			while (arg[i] != '\"' && arg[i])
				var_to_val(arg, &i, &res, env);
			i++;
		}
		else
			var_to_val(arg, &i, &res, env);
	}
	return (res);
}
