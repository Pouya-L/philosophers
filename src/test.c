/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:51:19 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 15:56:50 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	test_print_table_info(t_simulation *table)
{
	printf("Number of Philos: %ld\ntime_to_die: %ld\ntime_to_eat: %ld\n\
	time_to_sleep: %ld\nMeal_max_limit: %ld\n", table->philo_cnt, \
	table->time_to_die, table->time_to_eat, table->time_to_sleep, \
	table->meals_to_eat_full);
	return (0);
}

void	test_print_fork_data(t_simulation *table)
{
	int		i;
	t_forks	*fork;

	i = 0;
	while (i < table->philo_cnt)
	{
		fork = &table->forks[i];
		printf("Fork ID: %d\n", fork->fork_id);
		i++;
	}
}

void	test_print_philo_data(t_simulation *table)
{
	int			i;
	t_philos	*philo;

	i = 0;
	while (i < table->philo_cnt)
	{
		philo = &table->philos[i];
		printf("\nPhilo ID: %d\nMeals: %d\nTime since last meal: \
		%ld\nIs full: %d\n", \
		philo->philo_id, philo->meals_cnt, philo->last_meal_time, \
		philo->is_full);
		printf("\nFirst Fork: %d\nSecond Fork: %d\n", \
		philo->first_fork->fork_id, philo->second_fork->fork_id);
		i++;
	}
}
