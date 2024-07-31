/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/24 15:49:54 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include "get_next_line/get_next_line_bonus.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PIPE_INPUT 1
# define PIPE_OUTPUT 0
//============================================================

typedef struct s_malloc
{
	void				*ptr;
	struct s_malloc		*next;
}						t_malloc;

typedef struct s_list
{
	struct list			*prev;
	char				*centent;
	struct list			*next;
}						t_list;

typedef struct s_files_list
{
	char				*redirection;
	char				*file;
	int heredoc_fd; //<-------
	struct s_files_list	*next;
}						t_files_list;

typedef struct s_data
{
	char **args;            //--> cmd args ex: "ls" "-la"
	t_files_list *in_files; //
	t_files_list		*out_files;
	struct s_data *next; // next node
	struct s_data *prev; // prev node (not used yet)
}						t_data;

typedef struct s_all
{
	t_malloc			*malloc_list;
	t_list				*list;
}						t_all;

//== Garbage Collector ======================================

void					add_front(t_malloc **list, t_malloc *node);
t_malloc				*new_node(void *ptr);
void					*allocator(int size, int time, t_malloc *malloc_list);
void					free_allocator(t_malloc **list);

//== Parsing =================================================

void					redirector(t_data *data, char *cmd);
t_data					*lexer(char *str, char **env);
int						env_size(char **env);
t_data					*syntax_error(t_data *data);
void					redirection(t_data *data);
char					*find_expand(char **env, char *find);
void					expand_out_file(t_data *data, char **env);
void					expand_in_file(t_data *data, char **env);
void					expand(t_data *data, char **env);
void					*quotes(char *str, int *start, int *end);
char					*quotes_remove(char *str);
void	var_to_val(char *arg, int *i, char **res, char **env);
char					*catch_expnad(char *arg, char **env);
	//== Execution ===============================================

	void execution(t_data *data, int length, char ***env);
char					*check_relative_path(char *file);
char					*check_paths(char **env, char *cmd);
void					piping(t_data *data, int **pipes, int length, int i);
void					open_infiles(t_data *data);
void					open_outfiles(t_data *data);
int						open_heredoc(char *limiter);
void	exiter(t_data *data, int code); //-toke as builtin exit too-
//-- Builtins ------------------------------------------------

int						check_builtins(t_data *data, int is_parent,
							char ***env);
void					ft_env(char **env);
void					ft_pwd(void);
void					ft_cd(t_data *data);
void					ft_echo(t_data *data);
void					ft_unset(t_data *data, char ***env);
void					ft_export(t_data *data, char ***env);
//------------------------------------------------------------
//== Utils ===================================================
int						ft_isalnum(int c);
char					**ft_tabledup(char **tabe);
char					**ft_split(char const *s, char c);
size_t					count_words(char const *s, char c);
void					*ft_memmove(void *dst, const void *src, size_t len);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnjoin(char const *s1, char const *s2,
							size_t len);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
int	char_in_cmd(char *cmd, char c); /////////
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					ft_lstadd_back(t_data **lst, t_data *new);
t_data					*ft_lstnew(void);
char					**ft_tablejoin(char **table, char *new);
void					free_table(char **args);
void					del_elem_char(t_data *data, int i);
t_files_list			*add_last(t_files_list **head, t_files_list *new);
t_files_list			*make_new(char *redirection, char *file);
//============================================================

#endif
