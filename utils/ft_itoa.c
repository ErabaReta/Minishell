/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:48:40 by ayechcha          #+#    #+#             */
/*   Updated: 2024/08/11 13:48:40 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_digits(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		count++;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static char	*ismin(void)
{
	return (ft_strdup("-2147483648"));
}

static void	n_num(int *n, int *j)
{
	*n *= -1;
	*j = 0;
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	int		digits;
	char	*num;

	i = 0;
	j = 1;
	digits = count_digits(n);
	if (n == -2147483648)
		return (ismin());
	num = (char *)malloc(digits + 1);
	if (!num)
		return (NULL);
	if (n < 0)
	{
		num[i++] = '-';
		n_num(&n, &j);
	}
	while (i < digits)
	{
		num[(digits - j) - i++] = (n % 10) + 48;
		n /= 10;
	}
	num[i] = '\0';
	return (num);
}