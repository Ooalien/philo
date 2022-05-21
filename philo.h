/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:51:51 by abayar            #+#    #+#             */
/*   Updated: 2022/05/21 17:50:05 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				nph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meal;
	int				last_meal;
	size_t			start;
	int				i;
}	t_data;

// typedef struct s_philo
// {
// 	pthread_t
// }	t_philo;

int	is_num(char *s);
int	check_args(char **av);
int	ft_atoi(const char *str);

#endif