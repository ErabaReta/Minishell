/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:16:16 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/06 22:23:21 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_outfile_list	*ft_lstnew_outfile(char *redirection, char *file)
{
	t_outfile_list	*ptr;

	ptr = (t_outfile_list *)malloc(sizeof(t_outfile_list));
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr->redirection = redirection;
	ptr->file = file;
	ptr->next = NULL;
	return (ptr);
}

t_outfile_list	*ft_lstlast(t_outfile_list *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
	{
		return (lst);
	}
	return (ft_lstlast(lst->next));
}

void	ft_lstadd_back(t_outfile_list **lst, t_outfile_list *new)
{
	t_outfile_list	*last_node;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

void	redirector(t_data *data, char *cmd)
{
	int	in_count;
	int	out_count;
	int	i;
	char	**words;
	// int	locate;

	words = ft_split(cmd, ' ');
	in_count = 0;
	i = 0;
	///////////////////////////////////////
	while (words[i] != NULL)
	{
		// locate = char_in_cmd(&(cmd[i]), '<');
		// if (locate == -1)
		// 	break ;
		// i+= locate + 1;
		if (ft_strncmp(words[i], "<", 2) == 0)
			in_count++;
		i++;
	}
	////
	out_count = 0;
	i = 0;
	while (words[i] != NULL) //TODO make linked list instead each conatains redirection type ('>' or '>>') and the file name
	{
		// locate = char_in_cmd(&(cmd[i]), '>');
		// if (locate == -1)
		// 	break ;
		// i+= locate + 1;
		if (ft_strncmp(words[i], ">", 2) == 0)
			out_count++;
		i++;
	}
	////////////////////////////////////////
	data->args = (char **)malloc(sizeof(char *) * (count_words(cmd, ' ') - (out_count * 2) - (in_count * 2) + 1));
	// data->out_files = (char **)malloc(sizeof(char *) * (out_count + 1));
	data->out_files = NULL;
	data->in_files = (char **)malloc(sizeof(char *) * (in_count + 1));
	i = 0;
	int	j = 0;
	// int	k = 0;
	int	l = 0;
	while (words[i] != NULL)
	{
		if(ft_strncmp(words[i], "<", 2) == 0 && words[i + 1] != NULL)//TODO '<' not nessecery to be alone in one word it can be in the middle splitting two words
		{
			data->in_files[l] = ft_strdup(words[i + 1]);
			l++;
			i += 2;
		}
		else if(ft_strncmp(words[i], ">", 2) == 0 && words[i + 1] != NULL)//TODO '>' not nessecery to be alone in one word it can be in the middle splitting two words
		{
			// data->out_files[k] = ft_strdup(words[i + 1]);
			// k++;
			ft_lstadd_back(&data->out_files, ft_lstnew_outfile(">", ft_strdup(words[i + 1])));
			
			i += 2;
		}
		else if(ft_strncmp(words[i], ">>", 3) == 0 && words[i + 1] != NULL)//TODO '>' not nessecery to be alone in one word it can be in the middle splitting two words
		{
			// data->out_files[k] = ft_strdup(words[i + 1]);
			// k++;
			ft_lstadd_back(&data->out_files, ft_lstnew_outfile(">>", ft_strdup(words[i + 1])));
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
	data->in_files[l] = NULL;
//=======================================================
	// printf("out_files===============\n");
	// for ( t_outfile_list *tmp = data->out_files; tmp != NULL;tmp = tmp->next)
	// {
	// 	printf("files => %s\n", tmp->file);
	// 	printf("redirection => %s\n", tmp->redirection);
	// }
	// printf("in_files===============\n");
	// for ( int m = 0; data->in_files[m] != NULL; m++)
	// {
	// 	printf("%s\n", data->in_files[m]);
	// }
	// printf("args===============\n");
	// for ( int m = 0; data->args[m] != NULL; m++)
	// {
	// 	printf("%s\n", data->args[m]);
	// }
	// exit(0);///////////
}
// void out_redirector(t_data *data, char *cmd)
// {
// 	int	i;
// 	int	place;

// 	i = 0;
// 	place = -1;
// 	while (cmd[i] != '\0')
// 	{
// 		i = char_in_cmd(&(cmd[i]), '>');
// 		if (i == -1)
// 			break ;
// 		place = i;
// 	}
// 	if (place == -1)
// 		data->in_files = NULL;
// }