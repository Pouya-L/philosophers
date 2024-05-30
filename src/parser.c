/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:18:23 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/28 20:42:42 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief cheks the arguments passed to the program. assigns them to the
 * table struct. If any of the arguments are invalid, it will print an error
 * message and return 1.
 * @param argv the arguments passed to the program.
 * @param table the main struct holding all the data for the simulation.
 * @return 0 on success, 1 on failure.
 */
int	check_args(char **argv, t_simulation *table)
{
	table->philo_cnt = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		table->meals_to_eat_full = ft_atol(argv[5]);
		if (table->meals_to_eat_full <= 0 || table->meals_to_eat_full > INT_MAX)
			return (error_msg("Invalid meals_to_eat"));
	}
	else
		table->meals_to_eat_full = -1;
	if (table->philo_cnt <= 0 || table->philo_cnt > INT_MAX)
		return (error_msg("Invalid number of philosophers"));
	if (table->time_to_die <= 0 || table->time_to_die > INT_MAX)
		return (error_msg("Invalid time_to_die"));
	if (table->time_to_eat <= 0 || table->time_to_eat > INT_MAX)
		return (error_msg("Invalid time_to_eat"));
	if (table->time_to_sleep <= 0 || table->time_to_sleep > INT_MAX)
		return (error_msg("Invalid time_to_sleep"));
	return (0);
}
