/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/06/04 16:20:32 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define PIPE_INPUT 1
#define PIPE_OUTPUT 0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
// #include <readline/history.h>
# include "get_next_line/get_next_line_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_data
{
	char rederiction; // |    <     >    <<     >>   &&    ||
	char *cmd;
	struct s_data *next;
	struct s_data *prev;
}	t_data;



void execution(t_data *data, int length, char **env);
//=
char	**ft_split(char const *s, char c);
//=
void	*ft_memmove(void *dst, const void *src, size_t len);
//type | next cmd | prev-> ty

#endif