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
	cmd1->cmd = "ls -la";
	cmd1->rederiction = '|';
	cmd1->prev = NULL;

	t_data *cmd2 = (t_data *)malloc(sizeof(t_data));
	cmd2->cmd = "wc -l";
	cmd2->rederiction = 0;
	cmd2->prev = cmd1;

	cmd1->next = cmd2;
	cmd2->next = cmd1;
	
	execution(cmd1, 2, env);
	
	
	return (0);
}
