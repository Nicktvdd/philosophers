/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:09:50 by rrask             #+#    #+#             */
/*   Updated: 2023/06/19 13:12:18 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define ARG_MIN 5
# define ARG_MAX 6
# define RAS_MAX 2147483647
# define RAS_MIN -2147483648
# define MAX_PHILO 250
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h> // isdigit
# include <unistd.h>
# include <sys/time.h>

pthread_mutex_t my_mutex;

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
	size_t			last_supper;
	t_attr			*attr;
}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	gate;
}				t_mutex;


// locks that we need
// pthread_mutex_t msg; // lock for printing
// pthread_mutex_t death; // mandatory lock for death checking

/*philos.c*/
void	philos_join(t_philo *philos);
void	philos_spawn(t_philo *philos, pthread_mutex_t *gate);
void	philos_init(t_philo *philos, t_attr *attrib, t_mutex *mutex);
void	*philo_run(void *this);
int	governor(t_philo *philos, t_attr *attr, pthread_mutex_t	*forks);

/* eatsleepdierepeat.c */
void	print_state(size_t start_time, int philo_num, char *string);
int		hit_the_hay(size_t	sleepytime);
int		is_dead(size_t last_supper, size_t time_to_die);
void	eating(t_philo *philo, size_t time_to_eat);
void	sleeping(t_philo *philo, size_t time_to_sleep);
void	thinking(t_philo *philo);
size_t	get_time_ms(void);

/*utils.c*/
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putchar(char c);
void		ft_putstr(char *string);
void		ft_putnbr(int n);
// static void	ft_sub(char *str, int len, int n);
// static int	ft_len(int n, int *minus);
// char		*ft_itoa(int n);


/*errors.c*/
void	error_handler(char *str);

/*mutex.c*/
void	mutex_init(int num_philos, t_mutex *mutex);
void	mutex_destroy(int num_philos, t_mutex *mutex);
// void	forks_init(int num_philos, pthread_mutex_t	*forks);
// void	forks_destroy(int num_philos, pthread_mutex_t *forks);

#endif