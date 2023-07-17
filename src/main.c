/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:54:18 by nvan-den          #+#    #+#             */
/*   Updated: 2023/07/17 12:55:28 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	attr_set(t_attr *attr, int argc, char **argv)
{
	attr->philo_num = ft_atoi(argv[1]);
	attr->time_to_die = ft_atoi(argv[2]);
	attr->time_to_eat = ft_atoi(argv[3]);
	attr->time_to_sleep = ft_atoi(argv[4]);
	attr->times_must_eat = -1;
	if (argc == ARG_MAX)
		attr->times_must_eat = ft_atoi(argv[5]);
	if (attr->philo_num <= 0 || attr->time_to_die <= 0
		|| attr->time_to_eat <= 0 || attr->time_to_sleep <= 0)
	{
		printf("Arguments are invalid\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_attr	attributes;
	t_mutex	mutex;
	t_philo	philos[MAX_PHILO];

	if (argc < ARG_MIN || argc > ARG_MAX)
	{
		printf("Try again, punk.\n");
		return (1);
	}
	if (attr_set(&attributes, argc, argv))
		return (2);
	if (mutex_init(attributes.philo_num, &mutex))
		return (3);
	philos_init(philos, &attributes, &mutex);
	philos_spawn(philos, &mutex.gate);
	governor(philos, philos->attr);
	philos_join(philos);
	if (mutex_destroy(attributes.philo_num, &mutex))
		return (4);
	return (0);
}
