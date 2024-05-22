/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:14:17 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/22 16:32:00 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//correct input looks like: ./philo 5 800 200 200 7
// 5 - number of philosophers
// 800 - time_to_die
// 200 - time_to_eat
// 200 - time_to_sleep
// 7 - number_of_times_each_philosopher_must_eat

int	main(int argc, char **argv)
{
	t_simulation table;
	if (argc == 5 || argc == 6)
	{
		if (check_args(argv, &table))
			return (1);
		if (data_init(&table))
			return (free_everything(&table));
		if (start_simulation(&table))
			return (free_everything(&table));
	}
	else
		return (error_msg("Invalid number of arguments, use 5 or 6 arguments only"));
}
