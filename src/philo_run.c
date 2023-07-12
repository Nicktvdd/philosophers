/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:38:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/12 14:42:49 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_run(void *this)
{
	/* Start the philosopher logic here (Grab forks if odd number,
		eat if two forks, die if death is due, wait if only one fork.) */
	t_philo	*philo = (t_philo *)this;

		pthread_mutex_lock(philo->gate);
		pthread_mutex_unlock(philo->gate);
		if (philo->id % 2 == 0)
			hit_the_hay(philo, 10);
		
		while(1)
		{
			if (is_dead(philo))
				return (this);
			if (philo->attr->times_must_eat)
			{
				if (philo->times_eaten == philo->attr->times_must_eat)
				{
					printf("Philosopher %d has eaten enough.\n", philo->id);
					return (0);
				}
			}
			if (is_dead(philo, philo->attr->time_to_die))
			{
				return (0);
			}
			if (philo->id % 2 == 0)
			{
				pthread_mutex_lock(philo->l_fork);
				pthread_mutex_lock(philo->r_fork);
				eating(philo, philo->attr->time_to_eat);
				pthread_mutex_unlock(philo->l_fork);
				pthread_mutex_unlock(philo->r_fork);
				// printf("I am philosopher %d, I am even.\n", philo->id);
				//lock the right fork first.
			}
			else
			{
				pthread_mutex_lock(philo->r_fork);
				pthread_mutex_lock(philo->l_fork);
				eating(philo, philo->attr->time_to_eat);
				pthread_mutex_unlock(philo->r_fork);
				pthread_mutex_unlock(philo->l_fork);
				// printf("I am philosopher %d, I am odd.\n", philo->id);
				//Lock the left fork first.
			}
			// sleep
			sleeping(philo, philo->attr->time_to_sleep);
		}
	return (this);
}