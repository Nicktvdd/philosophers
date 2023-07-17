/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   governor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:51:33 by rrask             #+#    #+#             */
/*   Updated: 2023/07/17 11:48:33 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

static void	kill_all(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].attr->philo_num)
	{
		pthread_mutex_lock(philos[i].death);
		philos[i].died = 1;
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
}

int	dead_philo_check(t_philo *philos, t_attr *attr)
{
	int i;

	i = 0;
	while (i < attr->philo_num)
	{
		pthread_mutex_lock(philos[i].death);
		if (&philos[i]) // always true??
		{
			if (philos[i].died == 1)
			{
				printf("dead philo!\n");//
				pthread_mutex_unlock(philos[i].death);
				kill_all(philos);
				printf("%lu ", get_time_ms() - philos[i].attr->start_time);	
				printf("Philosopher %d is dead.\n", philos[i].id);
				return (1);
			}
		}
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
	return (0);
}

int	governor(t_philo *philos, t_attr *attr)
{
	int i;

	i = 0;
	usleep(500);//
	while (1)
	{
		if (dead_philo_check(philos, attr))
			return (1);
		if (attr->times_must_eat > 0)
		{
			pthread_mutex_lock(philos[i].death);
			if (philos[i].times_eaten == attr->times_must_eat)
			{
				printf("Philosopher %d has eaten enough.\n", philos[i].id);
				pthread_mutex_unlock(philos[i].death);
				return (1);
			}
			pthread_mutex_unlock(philos[i].death);
		}
	}
	return (0);
}
