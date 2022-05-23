/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:59:53 by abayar            #+#    #+#             */
/*   Updated: 2022/05/23 19:16:52 by abayar           ###   ########.fr       */
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

void	to_do(t_philo *philo, int index)
{
	if (index == 1)
	{
		philo->eating = 1;
		philo->last_meal = timenow();
		usleep(philo->data->t_eat * 1000);
		if (++philo->meals >= philo->data->n_meal && philo->data->n_meal != -1)
			philo->data->end++;
	}
	if (index == 2)
	{
		usleep(philo->data->t_sleep * 1000);
	}
}

void	print(t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->data->print);
	if (index == 0)
	{
		printf("%zu %d has taken a fork\n", timenow(), philo->id);
	}
	else if (index == 1)
	{
		printf("%zu %d is eating\n", timenow(), philo->id);
	}
	else if (index == 2)
	{
		printf("%zu %d is sleeping\n", timenow(), philo->id);
	}
	else if (index == 3)
	{
		printf("%zu %d is thinking\n", timenow(), philo->id);
	}
	pthread_mutex_unlock(&philo->data->print);
	to_do(philo, index);
}

void	*routine(void *arg)
{
	t_philo	*ph;
	
	ph = (t_philo *)arg;
	//usleep(1500);
	while (1)
	{
		pthread_mutex_lock(&ph->data->fork[ph->id - 1]);
		print(ph, 0);
		pthread_mutex_lock(&ph->data->fork[ph->id % ph->data->nph]);
		print(ph, 0);
		pthread_mutex_lock(&ph->data->dead[ph->id - 1]);
		print(ph,1);
		pthread_mutex_unlock(&ph->data->fork[ph->id - 1]);
		pthread_mutex_unlock(&ph->data->fork[ph->id % ph->data->nph]);
		ph->eating = 0;
		pthread_mutex_unlock(&ph->data->dead[ph->id - 1]);
		print(ph, 2);
		print(ph, 3);
	}
	return (NULL);
}

void	check_dead(t_philo *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while(i < data->nph)
		{
			if (!philo[i].eating)
			{
				pthread_mutex_lock(&philo->data->dead[i]);
				printf("_____________philo nbr %d_______________\n               Lat meal = %lu \n____________time now = %lu_____________\n", i+1, timenow() - philo[i].last_meal, timenow());
				if (timenow() - philo[i].last_meal >= data->t_die)
				{
					pthread_mutex_lock(&philo->data->print);
					printf("%zu %d died\n", timenow(), i + 1);
					return ;
				}
				if (data->end >= data->n_meal && data->n_meal != -1)
				{
					pthread_mutex_lock(&philo->data->print);
					return ;
				}
				pthread_mutex_unlock(&philo->data->dead[i]);
			}
			i++;
		}
		usleep(600);
	}
}

int	read_data(int ac, char **av, t_data *data)
{
	data->end = 0;
	data->nph = ft_atoi(av[1]);
	if (data->nph < 1)
		return (-1);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if(ac == 6)
	{
		data->n_meal = ft_atoi(av[5]);
		if (data->n_meal == 0)
			return (-1);
	}
	else
		data->n_meal = -1;
	return (0);
}

void	init_mutex(int x, t_data *data)
{
	int	i;

	i = 0;
	while(i < x)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->dead[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
}

void	even_philos(int i, t_data *data, t_philo *philo)
{
	while (i < data->nph)
	{
		if ((i + 1) % 2 == 0)
		{
			philo[i].id = i + 1;
			philo[i].meals = 0;
			philo[i].data = data;
			philo[i].eating = 0;
			philo[i].start = timenow();
			pthread_create(&philo[i].ph, NULL, routine, &philo[i]);
		}
		i++;
	}
}

void	odd_philos(int i, t_data *data, t_philo *philo)
{
	while (i < data->nph)
	{
		if ((i + 1) % 2 == 1)
		{
			philo[i].id = i + 1;
			philo[i].meals = 0;
			philo[i].data = data;
			philo[i].eating = 0;
			philo[i].start = timenow();
			pthread_create(&philo[i].ph, NULL, routine, (void *)&philo[i]);
		}
		i++;
	}
}

void	destroy(int x, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while(i < x)
	{
		pthread_detach(philo[i].ph);
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->dead[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	free(data->fork);
	free(data->dead);
	free(data);
	free(philo);
}

void	creat_philos(t_philo *philo, int x, t_data *data)
{
	int	i;
	
	data->i = 0;
	philo = malloc(sizeof(t_philo) * x);
	data->fork = malloc(sizeof(pthread_mutex_t) * x);
	data->dead = malloc(sizeof(pthread_mutex_t) * x);
	if (!philo || !data->fork || !data->dead)
	{
		write(2, "malloc fail\n", 12);
		exit(1);
	}
	init_mutex(x, data);
	i = 0;
	odd_philos(i, data, philo);
	usleep(1000);
	i = 0;
	even_philos(i, data, philo);
	check_dead(philo, data);
	//destroy(x, philo, data);
	pthread_mutex_destroy(&data->print);
	while(i < x)
	{
		pthread_detach(philo[i].ph);
		 pthread_mutex_destroy(&data->fork[i]);
		 pthread_mutex_destroy(&data->dead[i]);
		i++;
	}
}


int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data *));
	if (ac == 5 || ac == 6)
	{
		if (check_args(av) == 0)
		{
			write(2, "Error args\n", 11);
			return (1);
		}
		if (read_data(ac, av, data) == -1)
		{
			printf("Error\n");
			return (1);
		}
		creat_philos(philo, data->nph, data);
		//check_dead(philo, data);
		//destroy(data->nph, philo, data);
		//printf("%d\n", philo[0].id);
		//destroy(data->nph, philo, data);
	}
	return (0);
}
