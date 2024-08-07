/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/07 13:06:55 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	looper(t_env **env)
{
	char *str;
	t_data *tmp;

	signal_num(1);
	str = NULL;
	while (1)
	{
		str = readline("minishell $> ");
		if (str == NULL)
			break;
		if (ft_strlen(str) != 2 && str[0] != '\n')
			add_history(str);
		tmp = lexer(str, env_list_to_table(*env));
		if(tmp != NULL)
			execution(tmp, ft_lstsize(tmp), env);
	}
}

//returns the size of the NULL terminated 2D char pointer
int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char **put_env_on_heap(char **env)
{
	char	**new_env;
	int		i;
	
	new_env = (char **)malloc(sizeof(char *) * (env_size(env) + 1));// TODO check if malloc failed
	i = 0;
	while (i < env_size(env))
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)sig;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	struct sigaction	sigact;

	sigact.sa_sigaction = signal_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGINT, &sigact, NULL) != 0)
		return (1);
	 t_env *new_env = env_table_to_list(env);
	looper(&new_env);
	return (0);
}
