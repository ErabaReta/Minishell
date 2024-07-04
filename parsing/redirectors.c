/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:16:16 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/02 15:16:23 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirector(t_data *data, char *cmd)
{
	int	in_count;
	int	out_count;
	int	i;
	char	**words;
	int	locate;

	words = ft_split(cmd, ' ');
	in_count = 0;
	i = 0;
	///////////////////////////////////////
	while (cmd[i] != '\0')
	{
		locate = char_in_cmd(&(cmd[i]), '<');
		if (locate == -1)
			break ;
		i+= locate + 1;
		in_count++;
	}
	////
	out_count = 0;
	i = 0;
	while (cmd[i] != '\0') //TODO make linked list instead each conatains redirection type ('>' or '>>') and the file name
	{
		locate = char_in_cmd(&(cmd[i]), '>');
		if (locate == -1)
			break ;
		i+= locate + 1;
		out_count++;
	}
	////////////////////////////////////////
	data->args = (char **)malloc(sizeof(char *) * (count_words(cmd, ' ') - (out_count * 2) - (in_count * 2) + 1));
	data->out_files = (char **)malloc(sizeof(char *) * (out_count + 1));
	data->in_files = (char **)malloc(sizeof(char *) * (in_count + 1));
	i = 0;
	int	j = 0;
	int	k = 0;
	int	l = 0;
	while (words[i] != NULL)
	{
		if(ft_strncmp(words[i], "<", 1) == 0 && words[i + 1] != NULL)//TODO '<' not nessecery to be alone in one word it can be in the middle splitting two words
		{
			data->in_files[l] = ft_strdup(words[i + 1]);
			l++;
			i += 2;
		}
		else if(ft_strncmp(words[i], ">", 1) == 0 && words[i + 1] != NULL)//TODO '>' not nessecery to be alone in one word it can be in the middle splitting two words
		{
			data->out_files[k] = ft_strdup(words[i + 1]);
			k++;
			i += 2;
		}
		else
		{
			data->args[j] = ft_strdup(words[i]);
			j++;
			i++;
		}
	}
	data->out_files[k] = NULL;
	data->args[j] = NULL;
	data->in_files[l] = NULL;
//=======================================================
	// printf("out_files===============\n");
	// for ( int m = 0; data->out_files[m] != NULL; m++)
	// {
	// 	printf("%s\n", data->out_files[m]);
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