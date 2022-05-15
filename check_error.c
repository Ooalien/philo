/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:44:50 by abayar            #+#    #+#             */
/*   Updated: 2022/05/10 18:10:56 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && i == 0 && s[i + 1] != '\0')
		{
			i++;
			continue ;
		}
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	if (s[0] == '\0')
		return (0);
	return (1);
}

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_num(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] || s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int	check_rep(char **av)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (av[i])
// 	{
// 		j = 1;
// 		while (j < i)
// 		{
// 			if (ft_strcmp(av[i], av[j]) == 0
// 				|| ft_atoi(av[i]) == ft_atoi(av[j]))
// 			{
// 				return (0);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }
