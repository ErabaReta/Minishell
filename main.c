/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/09 20:16:37 by eouhrich         ###   ########.fr       */
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

void	looper(char ***env)
{
	char *str;
	int	size;
	str = readline("minishell $> ");
	t_data *tmp;
	
	while (str != NULL)
	{
		// printf("line=>\"%s\"\n", str);
		if (ft_strlen(str) != 2 && str[0] != '\n')
			add_history(str);
		tmp = mini_parsing(str, &size);
		execution(tmp, size, env);
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
	// struct sigaction	sigact;

	// sigact.sa_sigaction = sigint_handler;
	// sigact.sa_flags = SA_SIGINFO;
	// sigemptyset(&sigact.sa_mask);
	// if (sigaction(SIGINT, &sigact, NULL) != 0)
	// 	return (1);
	char **new_env = put_env_on_heap(env);
	looper(&new_env);
	// char *str;
	// int	size;
	// str = readline("minishell >$ ");
	// t_data *tmp;
	
	// while (str != NULL)
	// {
	// 	if (str[0] != '\0')
	// 		add_history(str);
	// 	tmp = mini_parsing(str, &size);
	// 	execution(tmp, size, env);
	// 	str = readline("minishell >$ ");
	// }

	/// ls -la | 
	// (void)ac;
	// (void)av;


	// t_data *cmd1 = (t_data *)malloc(sizeof(t_data));
	// cmd1->cmd = "ls -la";
	// cmd1->rederiction = '|';//0
	// cmd1->prev = NULL;
	// // cmd1->next = NULL;////

	// t_data *cmd2 = (t_data *)malloc(sizeof(t_data));
	// cmd2->cmd = "grep total";
	// cmd2->rederiction = '|';
	// cmd2->prev = cmd1;


	// t_data *cmd3 = (t_data *)malloc(sizeof(t_data));
	// cmd3->cmd = "wc -c";
	// cmd3->rederiction = 0;
	// cmd3->prev = cmd2;


	// cmd1->next = cmd2;
	// cmd2->next = cmd3;
	// cmd3->next = NULL;
	

	// execution(cmd1, 3, env);

	//===========================================
	// int *pipes = (int *)malloc(sizeof(int) * 2);
	// if (pipe(pipes) == -1)
	// {
	// 		printf("error : cant create pipe %d\n",-1);
	// }

	// int id1 = fork();

	// if (id1 == 0)
	// {
	// 	dup2(pipes[1], STDOUT_FILENO);
	// 	close(pipes[0]);
	// 	close(pipes[1]);
	// 	char **args = ft_split(cmd1->cmd, ' ');
	// 	execve(args[0], args, env);

	// }

	// id1 = fork();

	// if (id1 == 0)
	// {
	// 	dup2(pipes[0], STDIN_FILENO);
	// 	close(pipes[0]);
	// 	close(pipes[1]);
	// 	char **args = ft_split(cmd2->cmd, ' ');
	// 	execve(args[0], args, env);
	// }	
	
	// 	close(pipes[0]);
	// 	close(pipes[1]);

	// int i = 0;
	// while (i < 2)
	// {
	// 	wait(NULL);
	// 	i++;
	// }

	return (0);
}
