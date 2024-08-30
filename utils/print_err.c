/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:14:15 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/30 06:34:52 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *str)
{
	int	i;
	
	i = 0;
	while (str != NULL && str[i] != '\0')
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
}