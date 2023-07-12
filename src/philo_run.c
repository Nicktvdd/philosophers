/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:38:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/12 16:36:39 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	get_forked(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_stat(philo, "has taken a fork");
	if (philo->attr->philo_num == 1)
	{
		hit_the_hay(philo, philo->attr->time_to_die + 1);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (philo_check_death(philo))
	{
		pthread_mutex_unlock(philo->r_fork) return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork");
	eat(philo, philo->attr->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_run(void *this)
{
	t_philo *philo = (t_philo *)this;

	pthread_mutex_lock(philo->gate);
	pthread_mutex_unlock(philo->gate);
	if (philo->id % 2 == 0)
		hit_the_hay(philo, 10);

	while (1)
	{
		if (is_dead(philo))
			return (this);
		get_forked(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (this);
}