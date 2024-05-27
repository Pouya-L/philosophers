/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:13:53 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/27 11:49:05 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_health(t_philos *philo)
{
	long	elapsed_time;
	long	time_to_die;

	if (get_int(philo->mutex, &philo->is_full))
		return (1);
	elapsed_time = get_time(GET_TIME_MILLISEC) - get_long(philo->mutex, &philo->last_meal_time);
	time_to_die = (philo->table->time_to_die);
	if (elapsed_time > time_to_die)
		return (0);
	else
		return (1);
}

int	all_threads_running(t_simulation *table)
{
	int	active_thread_cnt;

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
