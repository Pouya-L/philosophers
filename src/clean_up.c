/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:17:17 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 15:52:30 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief frees the memory allocated for the forks.
 * @param table the main struct holding all the data for the simulation.
 * @return void
*/
void	free_forks(t_simulation *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->philo_cnt)
		{
			if (table->forks[i].fork_id != -1)
				mutex_op(MUTEX_DESTROY, &table->forks[i].fork);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
}

void	free_philo(t_simulation *table)
{
	int	i;

	i = 0;
	if (table->philos)
	{
		while (i < table->philo_cnt)
		{
			if (table->philos[i].mutex)
			{
				mutex_op(MUTEX_DESTROY, table->philos[i].mutex);
				free(table->philos[i].mutex);
				table->philos[i].mutex = NULL;
			}
			free(table->philos[i].thread_id);
			i++;
		}
		free(table->philos);
		table->philos = NULL;
	}
}

/**
 * @brief frees the memory allocated for the data in t_simulation struct.
 * @param table the main struct holding all the data for the simulation.
 * @return void
*/
int	free_everything(t_simulation *table)
{
	if (table->table_mutex)
	{
		mutex_op(MUTEX_DESTROY, table->table_mutex);
		free(table->table_mutex);
		table->table_mutex = NULL;
	}
	if (table->write_mutex)
	{
		mutex_op(MUTEX_DESTROY, table->write_mutex);
		free(table->write_mutex);
		table->write_mutex = NULL;
	}
	free_forks(table);
	free_philo(table);
	return (1);
}
