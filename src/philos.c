/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tn-denpoof <tn-denpoof@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:50:58 by rrask             #+#    #+#             */
/*   Updated: 2023/06/16 14:13:27 by tn-denpoof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	*philo_run(void *this)
{
	/* Start the philosopher logic here (Grab forks if odd number,
		eat if two forks, die if death is due, wait if only one fork.) */
	t_philo	*philo = (t_philo *)this;

		pthread_mutex_lock(philo->gate);
		pthread_mutex_unlock(philo->gate);
		while (1)
		{
			if (philo->attr->times_must_eat)
			{
				if (philo->times_eaten == philo->attr->times_must_eat)
				{
					printf("Philosopher %d has eaten enough.\n", philo->id);
					return (0);
			}
			//if (is_dead(philo, philo->attr->time_to_die))
				//exit (0);
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
	//if(start_time - philos[i].last_supper >= time_to_die)	condition of dying
	//	philo dies

void	philos_init(t_philo *philos, t_attr *attrib, t_mutex *mutex) // change to use t_mutex  pthread_mutex_t *forks
{
	int i;

	i = 0;
	while (i < attrib->philo_num)
	{
		philos[i].attr = attrib;
		philos[i].l_fork = &mutex->forks[i];
		if (i == attrib->philo_num - 1)
			philos[i].r_fork = &mutex->forks[0];
		else
			philos[i].r_fork = &mutex->forks[i + 1];
		philos[i].gate = &mutex->gate;
		philos[i].id = i;
		philos[i].is_dead = 0;
		philos[i].times_eaten = 0;
		philos[i].last_supper = get_time_ms();
		i++;
	}
}

void	philos_spawn(t_philo *philos, pthread_mutex_t *gate)
{
	int i;

	i = 0;
	pthread_mutex_lock(gate);
	while (i < philos->attr->philo_num)
	{
		pthread_create(&philos[i].thread, NULL, &philo_run, philos + i);
		i++;
	}
	pthread_mutex_unlock(gate);
}

void	philos_join(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->attr->philo_num)
	{
		pthread_join(philos[i].thread, NULL);
		printf("Philosopher %d has been terminated.\n", i);
		i++;
	}
}