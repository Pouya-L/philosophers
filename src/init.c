/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:00:31 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/16 12:11:49 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks_each(t_philos *philo, long philo_pos, t_forks *forks)
{
	long	philo_cnt;

	philo_cnt = philo->table->philo_cnt;
	if (philo->philo_id % 2)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_cnt];
	}
	else
	{
		philo->first_fork = &forks[(philo_pos + 1) % philo_cnt];
		philo->second_fork = &forks[philo_pos];
	}
}
/**
 *
*/
void	set_up_philos(t_simulation *table)
{
	long		i;
	t_philos	*philo;

	i = 0;
	while (i < table->philo_cnt)
	{
		philo = &table->philos[i];
		philo->philo_id = i;
		philo->meals_cnt = 0;
		philo->time_since_last_meal = 0;
		philo->is_full = 0;
		philo->table = table;
		assign_forks_each(philo, i, table->forks);
		i++;
	}

}

int	data_init(t_simulation *table)
{
	int	i;

	i  = 0;
	table->end_of_simulation = 0;
	table->forks = malloc(sizeof(t_forks) * table->philo_cnt);
	if (!table->forks)
		return (error_msg("data_init: table->forks: Malloc failed"));
	while (i < table->philo_cnt)
	{
		if (mutex_op(MUTEX_INIT, &table->forks[i].fork))
			return (1);
		table->forks[i].fork_id = i;
		i++;
	}
	table->philos = malloc(sizeof(t_philos) * table->philo_cnt);
	if (!table->philos)
		return (error_msg("data_init: table->philos: Malloc failed"));
	i = 0;
	set_up_philos(table);
	return (0);
}

int	mutex_op(t_opcode opcode, pthread_mutex_t *mutex)
{
	if (opcode == MUTEX_INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			return (error_msg("Mutex init failed"));
	}
	else if (opcode == MUTEX_LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (error_msg("Mutex lock failed"));
	}
	else if (opcode == MUTEX_UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			return (error_msg("Mutex unlock failed"));
	}
	else if (opcode == MUTEX_DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			return (error_msg("Mutex destroy failed"));
	}
	return (0);
}

int	p_thread_op(t_opcode opcode, pthread_t *thread, void *(*func)(void *), void *arg)
{
	if (opcode == THREAD_CREATE)
	{
		if (pthread_create(thread, NULL, func, arg))
			return (error_msg("Thread create failed"));
	}
	else if (opcode == THREAD_JOIN)
	{
		if (pthread_join(*thread, NULL))
			return (error_msg("Thread join failed"));
	}
	else if (opcode == THREAD_DETACH)
	{
		if (pthread_detach(*thread))
			return (error_msg("Thread detach failed"));
	}
	return (0);
}
