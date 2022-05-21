/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:59:53 by abayar            #+#    #+#             */
/*   Updated: 2022/05/21 17:28:45 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timenow(void)
{
	struct timeval	time;
	size_t t;

	t = 0;
	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (t);
}

void	eating_sleeping(t_data *data)
{
	usleep(data->t_eat * 1000);
	data->last_meal = data->start - timenow();
	usleep(data->t_sleep * 1000);
	//printf("8-------------8\n");
}

void	take_fork(t_data *data)
{
	//usleep(2000);
	pthread_mutex_lock(&data->fork[data->i]);
	pthread_mutex_lock(&data->fork[(data->i + 1) % data->nph]);
	eating_sleeping(data);
	printf("%d---------%d\n",data->i,(data->i + 1) % data->nph);
	pthread_mutex_unlock(&data->fork[data->i]);
	pthread_mutex_unlock(&data->fork[(data->i + 1) % data->nph]);
}

void	*routine(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;

	//usleep(200);
	printf("hello %d time is = %zu\n", data->i, timenow() - data->start);
	take_fork(data);
	return (NULL);
}

void	read_data(int ac, char **av, t_data *data)
{
	data->nph = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if(ac == 6)
	{
		data->n_meal = ft_atoi(av[5]);
	}
	else
	{
		data->n_meal = 0;
	}
}

void	creat_philos(pthread_t *th, int x, t_data *data)
{
	int	i;
	
	data->i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * x);
	th = malloc(sizeof(pthread_t) * x);
	if (!th)
	{
		write(2, "malloc fail\n", 12);
		exit(1);
	}
	i = 0;
	while(i < x)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	data->start = timenow();
	while (data->i < x)
	{
		pthread_create(&th[data->i], NULL, routine, data);
		usleep(200);
		data->i++;
	}
	i = 0;
	while (i < x)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	i = 0;
	while(i < x)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data *));
	data->nph = 0;
	data->t_die = 0;
	data->t_eat = 0;
	data->t_sleep = 0;
//	data->start = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_args(av) == 0)
		{
			write(2, "Error args\n", 11);
			return (1);
		}
		read_data(ac, av, data);
		creat_philos(data->th, data->nph, data);                                                          
	}
	return (0);
}
