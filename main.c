/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/10 21:00:55 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_spec	*get_specials()
{
	static t_spec	special_vars;

	return (&special_vars);
}

int	signal_num(int signal)
{
	static	int	num;

	num = 1;
	if (signal != -1)
		num = signal;
	return (num);
}

int	ft_lstsize(t_data *lst)
{
	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	return (1 + ft_lstsize(lst->next));
}

void	looper()
{
	char *str;
	t_data *tmp;

	signal_num(1);
	str = NULL;
	while (1)
	{
		str = readline("minishell $> ");
		if (str == NULL)
		{
			printf("exit\n");
			exiter(NULL, 0);
		}
		add_history(str);
		tmp = lexer(str, env_list_to_table());
		free(str);
		if (tmp != NULL)
			execution(tmp, ft_lstsize(tmp));
		free_all_heap();
	}

}

// //returns the size of the NULL terminated 2D char pointer
// int	env_size(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] != NULL)
// 		i++;
// 	return (i);
// }

// char **put_env_on_heap(char **env)
// {
// 	char	**new_env;
// 	int		i;

// 	new_env = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
// 	i = 0;
// 	while (i < env_size(env))
// 	{
// 		new_env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	return (new_env);
// }

void signal_handler(int sig)
{
	t_spec *svars = get_specials();
	// (void)info;
	// (void)context;
	(void)sig;

	svars->exit_status = 128 + sig;
	
	if (sig == SIGINT && is_herdoc(-1) == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	struct sigaction	sigact;
	t_spec *special_vars;
	
	(void)special_vars;
	sigact.sa_handler = signal_handler;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGINT, &sigact, NULL) != 0)
		return (1);
	special_vars = get_specials();
	env_table_to_list(env);
	looper();
	return (0);
}
