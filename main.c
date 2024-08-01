/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunter <hunter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/01 18:09:09 by hunter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// # include <signal.h>


// void	sigint_handler(int sig, siginfo_t *info, void *context)
// {
// 	(void)info;
// 	(void)sig;
// 	(void)context;
	
// 	write(1, "\n", 1);
// }

int	ft_lstsize(t_data *lst)
{
	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	return (1 + ft_lstsize(lst->next));
}

char	*get_last_arg(t_data *data)
{
	int	i;

	i = 0;
	if (data && data->next == NULL)
	{
		while (data->args[i + 1])
			i++;
		
	}
	return (data->args[i]);
}

void	looper(char ***env)
{
	char *str;
	//int	size;
	str = readline("minishell $> ");
	t_data *tmp;
	(void)env;
	(void)tmp;
	while (str != NULL)
	{
		if (ft_strlen(str) != 2 && str[0] != '\n')
			add_history(str);
    	tmp = lexer(str, *env);
		// if(tmp != NULL)
		// 	execution(tmp, ft_lstsize(tmp), env);
		str = readline("minishell $> ");
	}
}

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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_malloc	*malloc_list;

	(void)malloc_list;
	// struct sigaction	sigact;

	// sigact.sa_sigaction = sigint_handler;
	// sigact.sa_flags = SA_SIGINFO;
	// sigemptyset(&sigact.sa_mask);
	// if (sigaction(SIGINT, &sigact, NULL) != 0)
	// 	return (1);
	char **new_env = put_env_on_heap(env);
	looper(&new_env);
	return (0);
}
