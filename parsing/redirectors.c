/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:16:16 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/14 21:54:28 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// creates a new node frm data entered
t_files_list	*ft_lstnew_outfile(char *redirection, char *file)
{
	t_files_list	*ptr;

	ptr = (t_files_list *)malloc(sizeof(t_files_list));
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr->redirection = redirection;
	ptr->file = file;
	ptr->next = NULL;
	return (ptr);
}
// returns the last node of a linked list
t_files_list	*ft_lstlast_mo(t_files_list *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
	{
		return (lst);
	}
	return (ft_lstlast_mo(lst->next));
}
// adds a list at the end of a linked list
void	ft_lstadd_back_mo(t_files_list **lst, t_files_list *new)
{
	t_files_list	*last_node;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast_mo(*lst);
	last_node->next = new;
}
// counts the new size of the string after adding spaces before and after each redirection
int	calc_new_size(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;	
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"')
		{
			i++;
			count++;	
			while (cmd[i] != '\"' && cmd[i] != '\0')
			{
				i++;
				count++;	
			}
		}
		else if (cmd[i] == '\'')
		{
			i++;
			count++;	
			while (cmd[i] != '\'' && cmd[i] != '\0')
			{
				i++;
				count++;	
			}
		}
		if((cmd[i] != '\0') && ((cmd[i] == '>' && cmd[i + 1] == '>') || (cmd[i] == '<' && cmd[i + 1] == '<')))
		{
			count +=4;
			i +=2;	
		}
		else if ((cmd[i] != '\0') && (cmd[i] == '>' || cmd[i] == '<'))
		{
			count +=3;
			i++;
		}
		else 
		{
			count++;
			i++;
		}
	}
	return (count);
}
// handle redirection inside the word by splitting it from it by add space before splitting the entire cmd with space
char	*split_redirct_from_word(char *cmd)
{
	int	size;
	char *new_cmd;
	int	i;
	int	j;

	size = calc_new_size(cmd);
	new_cmd = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"')
		{
			new_cmd[j++] = cmd[i++];
			while (cmd[i] != '\"' && cmd[i] != '\0')
			{
				new_cmd[j++] = cmd[i++];
			}
		}
		else if (cmd[i] == '\'')
		{
			new_cmd[j++] = cmd[i++];
			while (cmd[i] != '\'' && cmd[i] != '\0')
			{
				new_cmd[j++] = cmd[i++];
			}
		}
		if((cmd[i] != '\0') && (cmd[i] == '>' && cmd[i + 1] == '>') )
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = '>';
			new_cmd[j++] = '>';
			new_cmd[j++] = ' ';
			i +=2;
		}
		else if ((cmd[i] != '\0') && cmd[i] == '<' && cmd[i + 1] == '<')
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = '<';
			new_cmd[j++] = '<';
			new_cmd[j++] = ' ';
			i +=2;
		}
		else if (cmd[i] != '\0' && cmd[i] == '>')
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = '>';
			new_cmd[j++] = ' ';
			i ++;
		}
		else if (cmd[i] != '\0' && cmd[i] == '<')
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = '<';
			new_cmd[j++] = ' ';
			i ++;
		}
		else 
		{
			new_cmd[j++] = cmd[i++];
		}
	}
	new_cmd[j] = '\0';
	free(cmd);////////////////////
	return (new_cmd);
}
// handling redirectors in each cmd if they exist
void	redirector(t_data *data, char *cmd)
{
	int	in_count;
	int	out_count;
	int	i;
	char	**words;

	cmd = split_redirct_from_word(cmd); // handle redirection inside the word by splitting it from it by add space before splitting the entire cmd with space
	words = ft_split(cmd, ' '); // splitiing the cmd into words
	in_count = 0;
	i = 0;
	///////////////////////////////////////
	while (words[i] != NULL)// calculating number of inFiles
	{
		if (ft_strncmp(words[i], "<", 2) == 0 || ft_strncmp(words[i], "<<", 3) == 0)
			in_count++;
		i++;
	}
	////
	out_count = 0;
	i = 0;
	while (words[i] != NULL) // calculating number of outFiles
	{
		if (ft_strncmp(words[i], ">", 2) == 0 || ft_strncmp(words[i], ">>", 3) == 0)
			out_count++;
		i++;
	}
	////////////////////////////////////////
	data->args = (char **)malloc(sizeof(char *) * (count_words(cmd, ' ') - (out_count * 2) - (in_count * 2) + 1));
	// data->out_files = (char **)malloc(sizeof(char *) * (out_count + 1));
	data->out_files = NULL;
	data->in_files = NULL;
	i = 0;
	int	j = 0;
	// int	k = 0;
	// int	l = 0;
	while (words[i] != NULL)
	{
		if(ft_strncmp(words[i], "<", 2) == 0  && words[i + 1] != NULL)
		{
			ft_lstadd_back_mo(&data->in_files, ft_lstnew_outfile("<", ft_strdup(words[i + 1])));
			i += 2;
		}
		else if (ft_strncmp(words[i], "<<", 3) == 0 && words[i + 1] != NULL)
		{
			ft_lstadd_back_mo(&data->in_files, ft_lstnew_outfile("<<", ft_strdup(words[i + 1])));
			i += 2;
		}
		else if(ft_strncmp(words[i], ">", 2) == 0 && words[i + 1] != NULL)
		{
			ft_lstadd_back_mo(&data->out_files, ft_lstnew_outfile(">", ft_strdup(words[i + 1])));
			i += 2;
		}
		else if(ft_strncmp(words[i], ">>", 3) == 0 && words[i + 1] != NULL)
		{
			ft_lstadd_back_mo(&data->out_files, ft_lstnew_outfile(">>", ft_strdup(words[i + 1])));
			i += 2;
		}
		else
		{
			data->args[j] = ft_strdup(words[i]);
			j++;
			i++;
		}
	}
	// data->out_files[k] = NULL;
	data->args[j] = NULL;
	// data->in_files[l] = NULL;
//=============== for Debug ========================================
	// printf("out_files===============\n");
	// for ( t_files_list *tmp = data->out_files; tmp != NULL;tmp = tmp->next)
	// {
	// 	printf("files => %s\n", tmp->file);
	// 	printf("redirection => %s\n", tmp->redirection);
	// }
	// printf("in_files===============\n");
	// for ( t_files_list *tmp = data->in_files; tmp != NULL;tmp = tmp->next)
	// {
	// 	printf("files => %s\n", tmp->file);
	// 	printf("redirection => %s\n", tmp->redirection);
	// }
	// printf("args===============\n");
	// for ( int m = 0; data->args[m] != NULL; m++)
	// {
	// 	printf("%s\n", data->args[m]);
	// }
	// exit(0);///////////
}
