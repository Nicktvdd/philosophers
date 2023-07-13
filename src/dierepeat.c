/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dierepeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:01:54 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/13 16:14:55 by nvan-den         ###   ########.fr       */
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
	printf("last supper %zu - start time %zu >= time_to_die %zu\n", philo->last_supper, philo->attr->start_time, philo->attr->time_to_die);
	printf("which is obviously: %zu\n", philo->last_supper - philo->attr->start_time);
	if (philo->last_supper - philo->attr->start_time >= philo->attr->time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->death);
		printf("hi from %i and he died omg\n", philo->id);//
		print_death(*philo);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	printf("hi from %i\n", philo->id);//
	return (0);
}

