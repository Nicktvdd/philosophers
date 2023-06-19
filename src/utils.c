/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:18 by rrask             #+#    #+#             */
/*   Updated: 2023/06/12 18:16:55 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		if (res * sign > RAS_MAX)
			return (-1);
		else if (res * sign < RAS_MIN)
			return (0);
		str++;
	}
	return ((int)res * sign);
}
static void	ft_sub(char *str, int len, int n)
{
	int	index;

	index = 0;
	if (n == 0)
	{
		str[index] = '0';
	}
	while (n != 0)
	{
		str[len - index - 1] = n % 10 + '0';
		n /= 10;
		index++;
	}
}

static int	ft_len(int n, int *minus)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			*minus = 1;
			return (10);
		}
		else
		{
			*minus = 1;
			n = -n;
		}
	}
	else if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		minus;
	int		len;

	minus = 0;
	len = ft_len(n, &minus);
	str = (char *)malloc(sizeof(char) * (len + minus + 1));
	if (!str)
		return (NULL);
	str[len + minus] = '\0';
	if (n == -2147483648)
	{
		str[10] = '8';
		n = 214748364;
		str[0] = '-';
		len--;
	}
	else if (minus == 1)
	{
		str[0] = '-';
		n = -n;
	}
	ft_sub(&str[minus], len, n);
	return (&str[0]);
}