/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:04:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/16 16:19:22 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff == NULL && get_specials()->pwd == NULL)
	{
		print_3_err("pwd: error retrieving current directory:",
			"getcwd: cannot access parent directories: ",
			"No such file or directory", -1);
		return (1);
	}
	else if (buff == NULL)
	{
		printf("%s\n", get_specials()->pwd);
	}
	else
	{
		printf("%s\n", buff);
		free(buff);
	}
	return (0);
}
