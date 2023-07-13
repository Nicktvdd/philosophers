/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dierepeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:01:54 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/13 14:53:05 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (philo->attr->start_time - philo->last_supper >= philo->attr->time_to_die)
	{
		pthread_mutex_unlock(philo->death);
		print_state(philo, "died\n");
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}

