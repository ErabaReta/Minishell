/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 00:39:25 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/17 00:39:25 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	long	r;
	int		i;
	int		signe;
	char	*num;

	r = 0;
	i = 0;
	signe = 1;
	num = (char *)str;
	if (str == NULL)
		return (0);
	while (num[i] == ' ' || (num[i] >= 9 && num[i] <= 13))
	{
		i++;
	}
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i++] == '-')
		{
			signe = -1;
		}
	}
	while (ft_isdigit(num[i]) == 1)
		r = r * 10 + (num[i++] - '0');
	return (r * signe);
}
