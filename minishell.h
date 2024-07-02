/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/02 10:47:35 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
#include <readline/history.h>
// # include "get_next_line/get_next_line_bonus.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define PIPE_INPUT 1
# define PIPE_OUTPUT 0
//============================================================

typedef struct s_data
{
	char *cmd;
	int in_rederiction;
	int out_rederiction;
	char	**args;
	char	**in_files;
	char	**out_files;
	struct s_data *next;
	struct s_data *prev; // not used yet
}	t_data;

//== Parsing =================================================

t_data	*mini_parsing(char *cmd_line, int *count);
void	redirector(t_data *data, char *cmd);
//== Execution ===============================================

void execution(t_data *data, int length, char **env);
char	*check_relative_path( char *file);
char	*check_paths(char **env, char *cmd);
void	exiter();
//== Utils ===================================================

char	**ft_split(char const *s, char c);
size_t	count_words(char const *s, char c);
void	*ft_memmove(void *dst, const void *src, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int char_in_cmd(char *cmd, char	c);/////////
//============================================================

#endif