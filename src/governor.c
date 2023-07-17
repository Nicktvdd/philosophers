/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   governor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:51:33 by rrask             #+#    #+#             */
/*   Updated: 2023/07/17 12:25:46 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int	is_starving(t_philo *philo)
{
	if (get_time_ms() - philo->last_supper >= philo->attr->time_to_die)
		return (1);
	return (0);
}

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
			if (is_starving(&philos[i]))
			{
				printf("dead philo!\n");//
				pthread_mutex_unlock(philos[i].death);
				kill_all(philos);
				printf("%lu ", get_time_ms() - philos[i].attr->start_time);	
				printf("Philosopher %d is dead.\n", philos[i].id);
				//philos_join(philos);
				return (1);
			}
		}
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
	return (0);
}
static int	check_eaten(t_philo *philos)
{
	int	i;
	int	philos_full;

	if (philos[0].attr->times_must_eat == -1)
		return (0);
	i = 0;
	philos_full = 0;
	while (i < philos[0].attr->philo_num)
	{
		pthread_mutex_lock(philos[i].death);
		if (philos[i].times_eaten >= philos[0].attr->times_must_eat)
			philos_full++;
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
	if (philos_full == philos[0].attr->philo_num)
	{
		kill_all(philos);
		return (1);
	}
	return (0);
}

int	governor(t_philo *philos, t_attr *attr)
{
	while (1)
	{
		if (dead_philo_check(philos, attr) || check_eaten(philos))
			return 1;
	}
	return 0;
}
