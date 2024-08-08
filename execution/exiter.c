/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:07:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/07 15:51:15 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exiter(t_data *data, int code)//TODO every exiter needs a freeier
{
	(void)data;
	free_all_heap();
	exit(code);
}