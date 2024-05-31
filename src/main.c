/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:14:17 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 16:02:03 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_simulation	table;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argv, &table))
			return (1);
		if (data_init(&table))
			return (free_everything(&table));
		if (start_simulation(&table))
			return (free_everything(&table));
		free_everything(&table);
	}
	else
		return (error_msg("Invalid number of arguments, use 5 or 6 arguments"));
}
