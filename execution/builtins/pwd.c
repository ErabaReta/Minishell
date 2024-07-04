/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:04:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/07/02 18:16:31 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(void)
{
	char *buff;

	buff = (char *)malloc(sizeof(char) * 100);//TODO get the correct size
	getcwd(buff, 100); //TODO get the correct size and check for errs
	printf("%s\n", buff);
	free(buff);
}
