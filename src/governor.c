/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   governor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:51:33 by rrask             #+#    #+#             */
/*   Updated: 2023/06/19 13:30:33 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

static int	dead_philo_check(t_philo *philos, t_attr *attr)
{
	int i;

	i = 0;
	while (i < attr->philo_num)
	{
		if (is_dead(philos[i].last_supper, attr->time_to_die) == 1)
		{
			/* print_state(philo->attr->start_time, philo->id, "is eating\n"); */
			printf("%lu ", get_time_ms() - philos[i].attr->start_time);	
			printf("Philosopher %d is dead.\n", philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	governor(t_philo *philos, t_attr *attr, pthread_mutex_t	*forks)
{
	int i;

	i = 0;
	(void)forks;
	while (1)
	{
		if (dead_philo_check(philos, attr))
			break;
		if (attr->times_must_eat)
		{
			if (philos[i].times_eaten == attr->times_must_eat)
			{
				printf("Philosopher %d has eaten enough.\n", philos[i].id);
				return (0);
			}
		}
	}
	return (0);
}
