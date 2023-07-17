/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:18 by rrask             #+#    #+#             */
/*   Updated: 2023/07/17 13:00:32 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_overflow(int min)
{
	if (min == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		min;

	i = 0;
	res = 0;
	min = 1;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
	{
		min = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if (res < 0)
			return (ft_overflow(min));
	}
	return ((int)res * min);
}

void	print_state(t_philo *philo, char *string)
{
	size_t	lapsed_time;

	pthread_mutex_lock(philo->print);
	lapsed_time = get_time_ms() - philo->attr->start_time;
	printf("%zu %d %s\n", lapsed_time, philo->id, string);
	pthread_mutex_unlock(philo->print);
}
