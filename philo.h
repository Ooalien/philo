/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:51:51 by abayar            #+#    #+#             */
/*   Updated: 2022/05/10 21:45:33 by abayar           ###   ########.fr       */
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
	pthread_t	*th;
	int			nph;
	int			t_die;
	int			t_eat;
	int			t_sleep;
}	t_data;

int	is_num(char *s);
int	check_args(char **av);
int	ft_atoi(const char *str);

#endif