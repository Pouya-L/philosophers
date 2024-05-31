/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:13:53 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 15:59:09 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief checks if the philo is healthy. ie not staved to death.
 * @param philo the philo struct to check.
 * @return 1 if the philo is healthy, 0 otherwise.
*/
int	philo_health(t_philos *philo)
{
	long	elapsed_time;
	long	time_to_die;

	if (get_int(philo->mutex, &philo->is_full))
		return (1);
	elapsed_time = get_time(GET_TIME_MILLISEC) - get_long(philo->mutex, \
	&philo->last_meal_time);
	time_to_die = (philo->table->time_to_die);
	if (elapsed_time > time_to_die)
		return (0);
	else
		return (1);
}

/**
 * @brief checks if all the threads are running in a thread safe way.
 * @param table the main struct holding all the data for the simulation.
 * @return 1 if all threads are running, 0 otherwise.
*/
int	all_threads_running(t_simulation *table)
{
	int	active_thread_cnt;

	active_thread_cnt = get_long(table->table_mutex, &table->philo_active_cnt);
	if (active_thread_cnt == table->philo_cnt)
		return (1);
	else
		return (0);
}

/**
 * @brief the monitor routine that checks the health of the philos.
 * It starts with a spinlock until all the philos have started running.
 * Then it checks the health of each philo in a loop.
 * If a philo has died, it prints a message & set the end_of_simulation flag.
 * @param data the main struct holding all the data for the simulation.
 * @return void
*/
void	*monitor_routine(void *data)
{
	t_simulation	*table;
	int				i;

	table = (t_simulation *)data;
	while (!all_threads_running(table))
	{
		ft_mysleep(50, table);
	}
	while (!is_sim_finished(table))
	{
		i = -1;
		while (++i < table->philo_cnt && !is_sim_finished(table))
		{
			if (philo_health(&table->philos[i]) == 0)
			{
				write_status(DIED, &table->philos[i], DEBUG);
				set_int(table->table_mutex, &table->end_of_simulation, 1);
			}
		}
	}
	return (NULL);
}
