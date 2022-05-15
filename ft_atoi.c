/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:26:04 by abayar            #+#    #+#             */
/*   Updated: 2022/05/10 18:05:25 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	checker(long long n)
{
	if (n > 2147483647 || n < -2147483648)
	{
		write(2, "Error\n", 6);
		exit(0);
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	long long	res;
	int			signe;
	int			i;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] == ' ') || (str[i] == '\t')
		|| (str[i] == '\n') || (str[i] == '\r')
		|| (str[i] == '\v') || (str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	res = checker(res * signe);
	return (res);
}
