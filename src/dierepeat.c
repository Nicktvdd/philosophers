/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dierepeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:01:54 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/14 15:38:37 by nvan-den         ###   ########.fr       */
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
	/* if (philo->id == 1)
		printf("%zu deathcheck start %i\n", get_time_ms() - philo->attr->start_time, philo->id);// */
	//pthread_mutex_lock(philo->death);
	/* if (philo->id == 1)
		printf("%zu deathcheck mid %i\n", get_time_ms() - philo->attr->start_time, philo->id);// */
	//printf("current time %zu - last supper %zu >= time_to_die %zu\n", get_time_ms(), philo->last_supper, philo->attr->time_to_die);
	//printf("which is obviously: %zu\n", get_time_ms() - philo->last_supper);
	if (get_time_ms() - philo->last_supper >= philo->attr->time_to_die)
	{
		philo->died = 1;
		//pthread_mutex_unlock(philo->death);
		print_death(*philo);
		return (1);
	}
	//pthread_mutex_unlock(philo->death);
	/* if (philo->id == 1)
		printf("%zu deathcheck end %i\n", get_time_ms() - philo->attr->start_time, philo->id);// */
	return (0);
}

