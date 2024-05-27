/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:00:31 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/27 10:40:24 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroy_fork_init(t_simulation *table, int i)
{
	while(i >= 0)
	{
		mutex_op(MUTEX_DESTROY, &table->forks[i].fork);
		i--;
	}
	return (1);
}

void	assign_forks_each(t_philos *philo, long philo_pos, t_forks *forks)
{
	long	philo_cnt;

	philo_cnt = philo->table->philo_cnt;
	if (philo->philo_id % 2 == 0)
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
int	set_up_philos(t_simulation *table)
{
	long		i;
	t_philos	*philo;

	i = 0;
	while (i < table->philo_cnt)
	{
		philo = &table->philos[i];
		philo->thread_id = malloc(sizeof(pthread_t));
		if (!philo->thread_id)
			return (error_msg("set_up_philos: thread_id: Malloc failed"));
		philo->philo_id = i;
		philo->meals_cnt = 0;
		philo->last_meal_time = 0;
		philo->is_full = 0;
		philo->table = table;
		assign_forks_each(philo, i, table->forks);
		philo->mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo->mutex)
				return (error_msg("set_up_philos: mutex Malloc	 failed"));
		if (mutex_op(MUTEX_INIT, philo->mutex))
			return (1);
		i++;
	}
	table->write_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->write_mutex)
		return (error_msg("set_up_philos:table->write_mutex: Malloc failed"));
	if (mutex_op(MUTEX_INIT, table->table_mutex))
		return (1);
	return (0);
}

int	data_init(t_simulation *table)
{
	int	i;

	i = -1;
	table->end_of_simulation = 0;
	table->all_thread_ready = 0;
	table->philo_active_cnt = 0;
	table->table_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->table_mutex)
		return (error_msg("data_init: table->table_mutex: Malloc failed"));
	if (mutex_op(MUTEX_INIT, table->table_mutex))
		return (1);
	table->forks = malloc(sizeof(t_forks) * table->philo_cnt);
	if (!table->forks)
		return (error_msg("data_init: table->forks: Malloc failed"));
	while (++i < table->philo_cnt)
	{
		if (mutex_op(MUTEX_INIT, &table->forks[i].fork))
			return (destroy_fork_init(table, i));
		table->forks[i].fork_id = i;
	}
	table->philos = malloc(sizeof(t_philos) * table->philo_cnt);
	if (!table->philos)
		return (error_msg("data_init: table->philos: Malloc failed"));
	if (set_up_philos(table))
		return (1);
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
