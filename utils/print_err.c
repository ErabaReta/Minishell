/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:14:15 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/04 02:32:15 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *err)
{
	if (err != NULL)
		write(STDERR_FILENO, err, ft_strlen(err));
}

void	print_3_err(char *str1, char *str2, char *str3, int code)
{
	char	*err;
	char	*tmp;

	err = NULL;
	err = ft_strnjoin(err, str1, 0);
	tmp = err;
	err = ft_strnjoin(err, str2, 0);
	ft_free(tmp);
	tmp = err;
	err = ft_strnjoin(err, str3, 0);
	ft_free(tmp);
	if (err != NULL)
		print_err(err);
	if (code != -1 && code != 0)
		exiter(code);
}
