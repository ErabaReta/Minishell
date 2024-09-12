/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/12 17:53:45 by ayechcha         ###   ########.fr       */
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
#include <sys/stat.h>

# define PIPE_INPUT 1
# define PIPE_OUTPUT 0
//============================================================

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
	t_files_list	*files; //
	struct s_data *next; // next node
	struct s_data *prev; // prev node (not used yet)
}						t_data;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_heap
{
	void	*ptr;
	struct s_heap	*next;
}						t_heap;

typedef	struct s_fd
{
	int	fd;
	struct s_fd	*next;
}	t_fd;

typedef struct s_spec
{
	t_env	*env;
	int		exit_status;
	// int		shlvl;
	char	*pwd;
	pid_t	child_p;
} t_spec;

//======main==============================

t_spec	*get_specials();
void	looper();
//== Garbage Collector ======================================

void	*mallocate(size_t	size);
void	free_all_heap();
void	ft_free(void *ptr);
void	store_fd(int fd);
void	clean_pool();
void	ft_close(int fd);
// void					add_front(t_malloc **list, t_malloc *node);
// t_malloc				*new_node(void *ptr);
// void					*allocator(int size, int time, t_malloc *malloc_list);
// void					free_allocator(t_malloc **list);

//== Parsing =================================================

void		redirector(t_data *data, char *cmd);
t_data		*lexer(char *str);
int			env_size(char **env);
void		redirection(t_data *data);
char		*find_expand(char *find, int q);
int			expand_file(t_data *data);
void		expand(t_data *data);
char		*quotes_remove(char *str, int *exp);
void		var_to_val(char *arg, int *i, char **res, int q);
char		**catch_expnad(char *arg);
int			open_heredoc(char *limiter);
void		quote_checker(char *arg, char **res, int *i, int q);
void		sighandler(int sig);
char		*ft_strdup2(const char *s1);
char		*quotes_adder(char *str);
int			isdou(char c);
t_data		*check_errors(t_data *data);
char		*last_arg(char	*s1);
void		set_last_arg(t_data *data);
//===Syntax_error============================================
t_data					*syntax_error_pipe(t_data *data);
t_data					*syntax_error_red(t_data *data);
int						syntax_error_her(t_data *data);
void					setup_signal_handler(int parent, void (*sig_handle)(int), void (*sig_ign)(int));
//== Execution ===============================================

void					execution(t_data *data, int length);
char					*check_relative_path(char *file);
char					*check_paths(char *cmd);
int						piping(int a_pipe[2], int length, int i, int fd_out);
int						open_outfile(t_files_list *file, int *fd);
int						open_infile(t_files_list *file, int *fd);
int						handle_files(t_files_list *files, int is_parent);
void					exiter(int code);
int						is_dir(char *path);
void	sighandler_exev(int sig);
void	sig_exit_exev(int sig);
//-- Builtins ------------------------------------------------

int		check_builtins(t_data *data, int is_parent);
int	ft_env(char **env, int is_parent);
int		ft_pwd(void);
int		ft_cd(t_data *data);
int	ft_echo(t_data *data);
int	ft_unset(t_data *data);
void	ft_export(t_data *data, int	*status);
t_env	*slice_var_value(char *str);
void		ft_exit(t_data *data, int is_parent, int *exit_status);
//------------------------------------------------------------
//== Utils ===================================================

char	**ft_tabledup(char **tabe);
char	**ft_tablejoin(char **table, char *new);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n, int p);
size_t	count_words(char const *s, char c);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnjoin(char const *s1, char const *s2, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		char_in_cmd(char *cmd, char	c);/////////
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_lstadd_back(t_data **lst, t_data *new);
t_data  *ft_lstnew();
int		ft_isalnum(int c);
int		ft_iswhitespace(int c);
int		ft_atoi(const char *str);
t_files_list	*add_last(t_files_list **head, t_files_list *new);
t_files_list	*make_new(char *redirection, char *file);
int	print_err(char *str);
int	ft_isdigit(int c);
int	include_space(char *str);
char	*ft_strchr(const char *s, int c);
void	print_3_err(char *str1, char *str2, char *str3, int code);
void	sort_table(char **table, int lenght);
char	*quotes_adder(char *str);
//== env ==========================================================

void	env_table_to_list(char **table);
t_env	*env_new_node(char *var, char *value);
char	**env_list_to_table();
t_env	*env_lstlast(t_env *env);
void	env_lst_addback(t_env *new);
t_env	*env_search(char *var);
char	*env_join_var_value(char *var, char *value);
char	**get_vars_sorted(void);
void	append_value(t_env	*env, char *value);
// char	**slice_var_value(char *str);////
//=================================================================
#endif
