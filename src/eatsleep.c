/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:01:59 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/17 12:09:31 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	hit_the_hay(t_philo *philo, size_t	sleepytime)
{
	size_t	the_time;

	the_time = get_time_ms();
	while (!is_dead(philo)
			&& (get_time_ms() - the_time) < sleepytime)
		usleep(500);
	return (0);
}

int	eat_the_hay(t_philo *philo, size_t	eating_time)
{
	size_t	the_time;

	the_time = get_time_ms();
	while ((get_time_ms() - the_time) < eating_time)
	{
		usleep(500);
		if(philo->died)
			return (1);//
	}
	return (0);
}

void	eating(t_philo *philo, size_t time_to_eat)
{
	pthread_mutex_lock(philo->death);
	if (is_starving(philo))
	{
		pthread_mutex_unlock(philo->death);
		return ;
	}
	philo->last_supper = get_time_ms();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->death);
	print_state(philo, "is eating");
	eat_the_hay(philo, time_to_eat);
	printf("%zu Philo %i has eaten %i times\n", get_time_ms() - philo->attr->start_time, philo->id, philo->times_eaten);
}

void	sleeping(t_philo *philo, size_t time_to_sleep)
{
	if (is_dead(philo)) // philo 1 is dying here?
		return ;
	print_state(philo, "is sleeping");
	hit_the_hay(philo, time_to_sleep);
}

void	thinking(t_philo *philo)
{
/* 	if (is_dead(philo))
		return ; */
	print_state(philo, "is thinking");
	//hit_the_hay(philo, 1);
}
