/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/15 14:51:17 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#include <readline/readline.h>

# include <signal.h>
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

typedef struct s_malloc {
  void *ptr;
  struct s_malloc *next;
}               t_malloc;

typedef struct s_list
{
  struct list *prev;
  char *centent;
  struct list *next;
}             t_list;

typedef struct	s_files_list
{
	char					*redirection;
	char					*file;
	struct	s_files_list	*next;
}	t_files_list;

typedef struct s_data
{
	char *cmd;  // --> ex: ls > out.txt -la 
	int in_rederiction; // not used anymore
	int out_rederiction; // not used anymore
	char  **args; //--> cmd args ex: "ls" "-la"
	t_files_list	*in_files;// TODO make the list , linked list instead of 2d array
	t_files_list	*out_files;
	struct s_data *next; // next node
	struct s_data *prev; // not used yet
}	t_data;

typedef struct s_all {
  t_malloc  *malloc_list;
  t_list    *list;
} t_all;


//== Garbage Collector ======================================

void  add_front(t_malloc **list, t_malloc *node);
t_malloc *new_node(void *ptr);
void  *allocator(int size, int time, t_malloc *malloc_list);
void  free_allocator(t_malloc **list);

//== Parsing =================================================

t_data	*mini_parsing(char *cmd_line, int *count);
void	redirector(t_data *data, char *cmd);
t_data	*lexer(char *str);
int		env_size(char **env);
//== Execution ===============================================

void	execution(t_data *data, int length, char ***env);
char	*check_relative_path( char *file);
char	*check_paths(char **env, char *cmd);
void	piping(t_data *data, int **pipes, int length, int i);
void	open_infiles(t_data *data);
void	open_outfiles(t_data *data);
void	exiter(t_data *data, int code);//-toke as builtin exit too-
//-- Builtins ------------------------------------------------

int		check_builtins(t_data *data, int is_parent, char ***env);
void	ft_env(char **env);
void	ft_pwd(void);
void	ft_cd(t_data *data);
void	ft_echo(t_data *data);
void	ft_unset(t_data *data, char ***env);
void	ft_export(t_data *data, char ***env);
//------------------------------------------------------------
//== Utils ===================================================

char	**ft_split(char const *s, char c);
size_t	count_words(char const *s, char c);
void	*ft_memmove(void *dst, const void *src, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int char_in_cmd(char *cmd, char	c);/////////
char  *ft_substr(char const *s, unsigned int start, size_t len);
//============================================================

#endif
