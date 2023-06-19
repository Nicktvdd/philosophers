/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepdierepeat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvn-den <nvn-den@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:23:43 by rrask             #+#    #+#             */
/*   Updated: 2023/06/16 14:57:26 by nvn-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_state(size_t start_time, int philo_num, char *string)
{
	size_t lapsed_time;

	lapsed_time = get_time_ms() - start_time;
	printf("%zu Philosopher %d %s", lapsed_time, philo_num, string);
/* 	ft_putnbr(lapsed_time);
	ft_putchar(' ');
	ft_putstr("Philosopher ");
	ft_putnbr(philo_num);
	ft_putchar(' ');
	ft_putstr(string); */
}

int	hit_the_hay(size_t	sleepytime)
{
	size_t	the_time;

	the_time = get_time_ms();
	while ((get_time_ms() - the_time) < sleepytime)
		usleep(500);
	return (0);
}
int	is_dead(t_philo *philo, size_t time_to_die)
{
	if (philo->attr->start_time - philo->last_supper >= time_to_die)
	{
		print_state(philo->attr->start_time, philo->id, "died\n");
		return (1);
	}
	return (0);
}

void	eating(t_philo *philo, size_t time_to_eat)
{
	philo->last_supper = get_time_ms();
	printf("Times eaten of %i: %i\n",philo->id, philo->times_eaten);
	print_state(philo->attr->start_time, philo->id, "is eating\n");
	hit_the_hay(time_to_eat);
	philo->times_eaten += 1;
}

void	sleeping(t_philo *philo, size_t time_to_sleep)
{
	print_state(philo->attr->start_time, philo->id, "is sleeping\n");
	hit_the_hay(time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_state(philo->attr->start_time, philo->id, "is thinking\n");
	hit_the_hay(1);
}

// void	

// /* int	main()
// {
// 	hit_the_hay(1000);
// 	return (0);
// } */
