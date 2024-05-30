/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/30 19:48:47 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char *str;
	printf("user >$ ");
	fflush(stdout);
	str = readline("");
	while (str != NULL)
	{
		printf("your command is %s\n", str);
		// free(str);
		printf("user >$ ");
		fflush(stdout);

		str = readline("");
	}
	return (0);
}
