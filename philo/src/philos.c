/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:56:58 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/17 12:57:24 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philos_init(t_philo *philos, t_attr *attrib, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < attrib->philo_num)
	{
		philos[i].attr = attrib;
		philos[i].l_fork = &mutex->forks[i];
		if (i == attrib->philo_num - 1)
			philos[i].r_fork = &mutex->forks[0];
		else
			philos[i].r_fork = &mutex->forks[i + 1];
		philos[i].gate = &mutex->gate;
		philos[i].death = &mutex->deaths[i];
		philos[i].print = &mutex->print;
		philos[i].id = i + 1;
		philos[i].died = 0;
		philos[i].times_eaten = 0;
		i++;
	}
}

void	philos_spawn(t_philo *philos, pthread_mutex_t *gate)
{
	int	i;

	(void)gate;
	i = 0;
	pthread_mutex_lock(gate);
	philos->attr->start_time = get_time_ms();
	while (i < philos->attr->philo_num)
	{
		thinking(philos + i);
		philos[i].last_supper = philos->attr->start_time;
		pthread_create(&philos[i].thread, NULL, &philo_run, philos + i);
		i++;
	}
	pthread_mutex_unlock(gate);
}

void	philos_join(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->attr->philo_num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
