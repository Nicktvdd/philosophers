/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junheepoofi <junheepoofi@student.hive.fi>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:51:23 by rrask             #+#    #+#             */
/*   Updated: 2023/06/12 16:28:02 by junheepoofi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	attr_set(t_attr *attr, int argc, char **argv)
{
	attr->philo_num = ft_atoi(argv[1]);
	attr->time_to_die = ft_atoi(argv[2]);
	attr->time_to_eat = ft_atoi(argv[3]);
	attr->time_to_sleep = ft_atoi(argv[4]);
	// attr->times_must_eat = -1;
	if (argc == ARG_MAX)
		attr->times_must_eat = ft_atoi(argv[5]);
	attr->start_time = get_time_ms();
	if (attr->philo_num <= 0 || attr->time_to_die <= 0 || attr->time_to_eat <= 0
		|| attr -> time_to_sleep <= 0 || attr -> times_must_eat <= 0)
	{
		printf("Arguments are invalid\n");
		return ;
	}
}

int	main(int argc, char **argv)
{
	t_attr			attributes;
	t_mutex			mutex;
	t_philo			philos[MAX_PHILO];

	if (argc < ARG_MIN || argc > ARG_MAX)
	{
		printf("Try again, punk.\n");
		return (0);
	}
	attr_set(&attributes, argc, argv);
	mutex_init(attributes.philo_num, &mutex);
	philos_init(philos, &attributes, &mutex);
	philos_spawn(philos, &mutex.gate);
	// loop the philos to check if philos have died
	philos_join(philos);
	mutex_destroy(attributes.philo_num, &mutex);
	return (0);
}
