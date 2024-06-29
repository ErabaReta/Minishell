/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/06/27 21:53:04 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
// #include <readline/history.h>
// # include "get_next_line/get_next_line_bonus.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define PIPE_INPUT 1
# define PIPE_OUTPUT 0
//============================================================
typedef struct s_data
{
	char rederiction; // '|'  not used
	char *cmd;
	struct s_data *next;
	struct s_data *prev; // not used yet
}	t_data;

//== Parsing =================================================

//== Execution ===============================================
void execution(t_data *data, int length, char **env);

//== Utils ===================================================
char	**ft_split(char const *s, char c);
void	*ft_memmove(void *dst, const void *src, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
//============================================================

#endif