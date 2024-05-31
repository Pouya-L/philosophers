/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:00 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 16:04:24 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief sleeps for the given time. If the simulation is finished, it will break
 * out of the loop. This is more accurate than just using usleep.
 * @param time_to_sleep the time to sleep in microseconds.
 * @param table the main struct holding all the data for the simulation.
 * @return void
*/
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
			usleep(remaining_time / 2);
		else
		{
			usleep(50);
		}
	}
}

/**
 * @brief gets the current time in seconds, milliseconds or microseconds.
 * @param op the opcode to specify the time format.
 * @return the time in the specified format.
*/
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

/**
 * @brief prints an error message in red and then returns 1.
 * @param msg the message to print.
 * @return 1
*/
int	error_msg(char *msg)
{
	printf("%s%s%s\n", RED, msg, DEFAULT);
	return (1);
}

/**
 * @brief returns the LONG_MAX or LONG_MIN if ft_atol faces an overflow.
 * @param sign the sign of the number.
 * @return LONG_MAX or LONG_MIN.
*/
long	ft_l_overflow_err(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

/**
 * @brief converts a string to a long.
 * It also will check for any overflow errors.
 * @param str the string to convert.
 * @return the long value of the string.
*/
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
