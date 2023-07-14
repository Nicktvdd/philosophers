/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:22:23 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/14 13:24:36 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char *string)
{
	size_t lapsed_time;

	pthread_mutex_lock(philo->print);
/* 	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->print);
		return ;
	} */
	lapsed_time = get_time_ms() - philo->attr->start_time;
	printf("%zu philosopher %d %s\n", lapsed_time, philo->id, string);
	pthread_mutex_unlock(philo->print);
}

void	print_death(t_philo philo)
{
	size_t	lapsed_time;
	
	pthread_mutex_lock(philo.print);
	lapsed_time = get_time_ms() - philo.attr->start_time;
	printf("%zu philosopher %d %s\n", lapsed_time, philo.id, "died");
	pthread_mutex_unlock(philo.print);
}