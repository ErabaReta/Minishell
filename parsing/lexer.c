/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 01:30:51 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/31 20:08:24 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		while (str[start] && ft_iswhitespace(str[start]) == 1)
		{
			start++;
		}
		while (str[start] && str[start] != '|' && ft_iswhitespace(str[start]) == 0)
		{
			quote = '\0';
			end = start;
			if (str[start] == '<' || str[start] == '>')
			{
				quote = str[start];
				end = start;
				while (str[end] == quote && str[end])
					end++;
			}
			while (str[end] && ft_iswhitespace(str[end]) == 0 && str[end] != '|'
				&& str[end] != '<' && str[end] != '>' && str[end] != '<'
				&& str[end] != '>' && quote == '\0')
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
				quote = '\0';
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

char	*last_arg(char	*s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_data	*lexer(char *str)
{
	int		i;
	t_data	*data;
	t_data	*new;
	t_spec	*svars;

	i = 0;
	data = NULL;
	svars = get_specials();
	str = ft_strnjoin(str, " ", 1);
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
	{
		svars->exit_status = 2;
		return (NULL);
	}
	redirection(data);
	if (!syntax_error_her(data))
		return (NULL);
	expand(data);
	if (!expand_file(data))
		return (NULL);
	i = 0;
	if (data->args && data->next == NULL)
	{
		while (data->args[i] && data->args[i + 1])
			i++;
		
		//===== resolving SEGV prob ===============
		t_env *env_node = env_search("_");
		if (env_node == NULL)
			env_lst_addback(env_new_node(ft_strdup2("_"), last_arg(data->args[i])));
		else
		{
			free(env_search("_")->value);
			env_search("_")->value = last_arg(data->args[i]);		
		}
		//==========================================
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
	// 	printf("files ====================== \n");

	// 	while (data->files)
	// 	{
	// 		printf("red = %s, file = %s, fd = %d\n", data->files->redirection,
	// 			data->files->file, data->files->heredoc_fd);
	// 		data->files = data->files->next;
	// 	}
	// 	data = data->next;
	// 	if (data != NULL)
	// 		printf("|\n");
	// }
	// // ==================================================
	return (data);
}








