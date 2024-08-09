/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 01:30:51 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/09 14:53:10 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_maker(char *first, char *second)
{
	char	*str;

	str = ft_strnjoin(first, second, 0);
	return (str);
}

t_data	*ft_split_args(char *str, int *i)
{
	int		start;
	int		end;
	char	*cmd;
	t_data	*data;
	char	**args;
	char	quote;

	start = *i;
	end = 0;
	data = ft_lstnew();
	args = (char **)mallocate(sizeof(char *));
	args[0] = NULL;
	while (str[start] && str[start] != '|')
	{
		while (str[start] && str[start] == ' ')
			start++;
		while (str[start] && str[start] != '|' && str[start] != ' ')
		{
			end = start;
			if (str[start] == '<' || str[start] == '>')
			{
				quote = str[start];
				end = start;
				while (str[end] == quote && str[end])
					end++;
			}
			while (str[end] && str[end] != ' ' && str[end] != '|'
				&& str[start] != '<' && str[start] != '>' && str[end] != '<'
				&& str[end] != '>')
			{
				if (str[end] == '\"' || str[end] == '\'')
				{
					quote = str[end];
					end++;
					while (str[end] != quote && str[end])
						end++;
					if (str[end] == '\0')
						return (NULL);
				}
				end++;
			}
			cmd = ft_substr(str, start, end - start);
			if (cmd == NULL)
				return (NULL);
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

char	*last_arg(char *last_arg)
{
	static char	*last;
	
	if (last_arg != NULL)
		last = ft_strdup(last_arg);
	return (last);
}

t_data	*lexer(char *str, char **env)
{
	int		i;
	t_data	*data;
	t_data	*new;

	i = 0;
	data = NULL;
	str = ft_strnjoin(str, " ", 1);
	(void)env;
	while (str[i])
	{
		new = ft_split_args(str, &i);
		if (new == NULL)
		{
			printf("syntax error near unexpected token\n");
			return (NULL);
		}
		ft_lstadd_back(&data, new);
	}
	if (!syntax_error_pipe(data) || !syntax_error_red(data))
		return (NULL);
	redirection(data, env);
	if (!syntax_error_her(data))
		return (NULL);
	expand(data, env);
	expand_in_file(data, env);
	expand_out_file(data, env);
	i = 0;
	if (data->args && data->next == NULL)
	{
		while (data->args[i] && data->args[i + 1])
			i++;
		last_arg(data->args[i]);
	}

	//=== for debug ==================================
	// i = 0;
	// while (data)
	// {
	// 	i = 0;
	// 	printf("args ====================== \n");
	// 	while (data->args && data->args[i])
	// 	{
	// 		printf("cmd = %s\n", data->args[i]);
	// 		i++;
	// 	}
	// 	printf("in_files ====================== \n");

	// 	while (data->in_files)
	// 	{
	// 		printf("red = %s, file = %s\n", data->in_files->redirection,
	// 			data->in_files->file);
	// 		data->in_files = data->in_files->next;
	// 	}
	// 	printf("out_files ====================== \n");
	// 	while (data->out_files)
	// 	{
	// 		printf("red = %s, file = %s\n", data->out_files->redirection,
	// 			data->out_files->file);
	// 		data->out_files = data->out_files->next;
	// 	}
	// 	data = data->next;
	// 	if (data != NULL)
	// 		printf("|\n");
	// }
	// ==================================================
	return (data);
}
