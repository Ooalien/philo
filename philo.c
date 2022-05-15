/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:59:53 by abayar            #+#    #+#             */
/*   Updated: 2022/05/10 23:57:53 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	printf("hello %d\n", data->t_sleep);
	return (NULL);
}

void	read_data(char **av, t_data *data)
{
	data->nph = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
}

void	creat_philos(pthread_t *th, int x, t_data *data)
{
	int	i;

	i = 0;
	th = malloc(sizeof(pthread_t) * x);
	if (!th)
	{
		write(2, "malloc fail\n", 12);
		exit(1);
	}
	while (i < x)
	{
		pthread_create(&th[i], NULL, routine, data);
		i++;
	}
	i = 0;
	while (i < x)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	data.nph = 0;
	data.t_die = 0;
	data.t_eat = 0;
	data.t_sleep = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_args(av) == 0)
		{
			write(2, "Error args\n", 11);
		}
		read_data(av, &data);
		creat_philos(data.th, data.nph, &data);
	}
	return (0);
}
