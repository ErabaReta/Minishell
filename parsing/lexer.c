/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 01:30:51 by ayechcha          #+#    #+#             */
/*   Updated: 2024/09/16 15:30:39 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checker_in_line(char *str, int *end, char quote)
{
	if (str[*end] && ft_iswhitespace(str[*end]) == 0 && str[*end] != '|'
		&& str[*end] != '<' && str[*end] != '>' && str[*end] != '<'
		&& str[*end] != '>' && quote == '\0')
		return (1);
	return (0);
}

int	split_helper(char *str, int *start, int *end)
{
	char	quote;

	quote = '\0';
	if (str[*start] == '<' || str[*start] == '>')
	{
		quote = str[*start];
		*end = *start + 1;
		if (str[*start + 1] && str[*start] == str[*start + 1])
			*end = *start + 2;
	}
	while (checker_in_line(str, end, quote))
	{
		if (str[*end] == '\"' || str[*end] == '\'')
		{
			quote = str[*end];
			(*end)++;
			while (str[*end] != quote && str[*end])
				(*end)++;
			if (str[*end] == '\0')
				return (0);
		}
		quote = '\0';
		(*end)++;
	}
	return (1);
}

void	init_data(t_data **data, char ***args)
{
	*data = ft_lstnew();
	*args = (char **)mallocate(sizeof(char *));
	*args[0] = NULL;
}

t_data	*ft_split_args(char *str, int *i, int start, int end)
{
	char	*cmd;
	t_data	*data;
	char	**args;

	init_data(&data, &args);
	while (str[start] && str[start] != '|')
	{
		while (str[start] && ft_iswhitespace(str[start]) == 1)
			start++;
		while (str[start] && str[start] != '|' && !ft_iswhitespace(str[start]))
		{
			end = start;
			if (!split_helper(str, &start, &end))
				return (NULL);
			cmd = ft_substr(str, start, end - start);
			start = end;
			args = ft_tablejoin(args, cmd);
		}
	}
	if (str[start] == '|')
		start++;
	*i = start;
	data->args = args;
	return (data);
}

t_data	*lexer(char *str)
{
	int		i;
	t_data	*data;
	t_data	*new;

	i = 0;
	data = NULL;
	if (str && str[0] != '\0')
		str = ft_strnjoin(str, " ", 1);
	while (str[i])
	{
		new = ft_split_args(str, &i, i, 0);
		if (new == NULL)
		{
			get_specials()->exit_status = 2;
			print_err("syntax error near unexpected token\n");
			return (NULL);
		}
		ft_lstadd_back(&data, new);
	}
	if (data && !check_errors(data))
		return (NULL);
	if (data)
		get_specials()->exit_status = 0;
	set_last_arg(data);
	return (data);
}
