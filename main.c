/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/06/04 16:14:52 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int	main(int ac, char **av, char **env)
{
	// char *str;
	// printf("user >$ ");
	// fflush(stdout);
	// str = readline("");
	// while (str != NULL)
	// {
	// 	printf("your command is %s\n", str);
	// 	// free(str);
	// 	printf("user >$ ");
	// 	fflush(stdout);

	// 	str = readline("");
	// }



	/// ls -la | 
	(void)ac;
	(void)av;


	t_data *cmd1 = (t_data *)malloc(sizeof(t_data));
	cmd1->cmd = "/usr/bin/ls -la";
	cmd1->rederiction = '|';//0
	cmd1->prev = NULL;
	// cmd1->next = NULL;////


	t_data *cmd2 = (t_data *)malloc(sizeof(t_data));
	cmd2->cmd = "/usr/bin/grep total";
	cmd2->rederiction = '|';
	cmd2->prev = cmd1;



	t_data *cmd3 = (t_data *)malloc(sizeof(t_data));
	cmd3->cmd = "/usr/bin/wc -c";
	cmd3->rederiction = 0;
	cmd3->prev = cmd2;


	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = NULL;
	

	execution(cmd1, 3, env);

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
