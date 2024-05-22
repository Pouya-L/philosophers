/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:00 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/22 13:43:29 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


//usleep majaorityy of time and then do some cpu intensive loops
//uses spinlock so I don't want to use it
void	godly_usleep(long time_to_sleep, t_simulation *table)
{
	long	start_time;
	long	elapsed_time;
	long	remaining_time;

	start_time = get_time(GET_TIME_MICROSEC);
	while (get_time(GET_TIME_MICROSEC) - start_time < time_to_sleep)
	{
		if (is_sim_finished(table))
			break ;
		elapsed_time = get_time(GET_TIME_MICROSEC) - start_time;
		remaining_time = time_to_sleep - elapsed_time;
		if (remaining_time > 1000)
			usleep(time_to_sleep / 2);
		else
		{
			while (get_time(GET_TIME_MICROSEC) - start_time < time_to_sleep)
				;

		}
	}
}

void	ft_mysleep(long time_to_sleep, t_simulation *table)
{
	long	start_time;
	long	elapsed_time;
	long	remaining_time;

	start_time = get_time(GET_TIME_MICROSEC);
	while (get_time(GET_TIME_MICROSEC) - start_time < time_to_sleep)
	{
		if (is_sim_finished(table))
			break ;
		elapsed_time = get_time(GET_TIME_MICROSEC) - start_time;
		remaining_time = time_to_sleep - elapsed_time;
		if (remaining_time > 1000)
			usleep(time_to_sleep / 2);
		else
		{
			usleep(50);
		}
	}
}

long	get_time(t_opcode op)
{
	struct timeval	time_val;
	long			time_in_s;
	long			time_in_ms;
	long			time_in_us;

	gettimeofday(&time_val, NULL);
	time_in_s = time_val.tv_sec + time_val.tv_usec / 1000000;
	time_in_ms = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
	time_in_us = time_val.tv_sec * 1000000 + time_val.tv_usec;
	if (op == GET_TIME_MILLISEC)
		return (time_in_ms);
	else if (op == GET_TIME_MICROSEC)
		return (time_in_us);
	else if (op == GET_TIME_SECONDS)
		return (time_in_s);
	else
		return (time_in_s);
}

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
