/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:13:53 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/22 18:14:16 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_health(t_philos *philo)
{
	long	elapsed_time;
	long	time_to_die;

	elapsed_time = get_time(GET_TIME_MICROSEC) - get_long(philo->mutex, &philo->last_meal_time);
	time_to_die = (philo->table->time_to_die) * 1000;
	if (get_int(philo->mutex, &philo->is_full))
		return (1);
	if (elapsed_time > time_to_die)
		return (0);
	else
		return (1);
}

int	all_threads_runnign(t_simulation *table)
{
	int	res;
	int	active_thread_cnt;

	res = 0;
	active_thread_cnt = get_long(table->table_mutex, &table->philo_active_cnt);
	if (active_thread_cnt == table->philo_cnt)
		return (1);
	else
		return (0);
}

void	*monitor_routine(void *data)
{
	t_simulation *table;
	int	i;

	table = (t_simulation *)data;

	//spinlock until all threads are running
	while (!all_threads_runnign(table))
		;
	while (!is_sim_finished(table))
	{
		i = -1;
		while (++i < table->philo_cnt && !is_sim_finished(table))
		{
			if (philo_health(&table->philos[i]) == 0)
			{
				set_int(table->table_mutex, &table->end_of_simulation, 1);
				write_status(DIED, &table->philos[i], DEBUG);
			}
		}
	}
}
