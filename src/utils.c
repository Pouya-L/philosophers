/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:00 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/16 11:53:38 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_msg(char *msg)
{
	printf("%s%s%s\n", RED, msg, DEFAULT);
	return (1);
}

long	ft_l_overflow_err(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	value;
	long	i;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i++] == '-')
				sign = sign * -1;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			if (value > (LONG_MAX - (str[i] - '0')) / 10)
				return (ft_l_overflow_err(sign));
			value = value * 10 + (str[i++] - '0');
		}
		break ;
	}
	return (value * sign);
}
