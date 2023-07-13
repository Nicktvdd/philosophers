/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:09:50 by rrask             #+#    #+#             */
/*   Updated: 2023/07/13 15:59:24 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define ARG_MIN 5
# define ARG_MAX 6
# define MAX_PHILO 250
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_attr
{
	size_t		start_time;
	int			philo_num;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			times_must_eat;
}					t_attr;

typedef struct s_philo
{
	unsigned int	id;
	int				is_dead;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*gate;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
	size_t			last_supper;
	t_attr			*attr;
}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t deaths[MAX_PHILO];
	pthread_mutex_t	gate;
	pthread_mutex_t	print;
}				t_mutex;

/*philos.c*/
void	philos_join(t_philo *philos);
void	philos_spawn(t_philo *philos, pthread_mutex_t *gate);
void	philos_init(t_philo *philos, t_attr *attrib, t_mutex *mutex);

/*governor.c*/
int		governor(t_philo *philos, t_attr *attr);

/*philo_run.c*/
void	*philo_run(void *this);

/* eatsleep.c */
int		hit_the_hay(t_philo *philo, size_t	sleepytime);
void	eating(t_philo *philo, size_t time_to_eat);
void	sleeping(t_philo *philo, size_t time_to_sleep);
void	thinking(t_philo *philo);

/*dierepeat.c*/
size_t	get_time_ms(void);
int		is_dead(t_philo *philo);

/*utils.c*/
int	ft_atoi(const char *str);

/*errors.c*/
void	error_handler(char *str);

/*mutex.c*/
int		mutex_init(int num_philos, t_mutex *mutex);
int		mutex_destroy(int num_philos, t_mutex *mutex);

/*printing.c*/
void	print_death(t_philo philo);
void	print_state(t_philo *philo, char *string);

#endif