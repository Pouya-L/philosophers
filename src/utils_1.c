/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:16:56 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/31 14:33:57 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Wrapper function for pthread mutex operations.
 * If it fails, it prints an error message.
 * @param opcode the operation to be performed.
 * @param mutex the mutex to be operated on.
 * @return 0 on success, 1 on failure.
*/
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

/**
 * @brief Wrapper function for pthread operations.
 * If it fails, it prints an error message.
 * @param opcode the operation to be performed.
 * @param thread the thread to be operated on.
 * @param func the function to be executed by the thread.
 * @param arg the argument to be passed to the function.
 * @return 0 on success, 1 on failure.
*/
int	p_thread_op(t_opcode opcode, pthread_t *thread, \
	void *(*func)(void *), void *arg)
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

/**
 * @brief checks if the simulation has finished in a thread safe way.
 * @param table the main struct holding all the data for the simulation.
 * @return int 1 if the simulation has finished, 0 otherwise.
*/
int	is_sim_finished(t_simulation *table)
{
	return (get_int(table->table_mutex, &table->end_of_simulation));
}

void	init_table_philo_util(t_simulation *table, t_philos *philo, \
		int type, int i)
{
	if (type == 0)
	{
		(void)i;
		table->end_of_simulation = 0;
		table->all_thread_ready = 0;
		table->philo_active_cnt = 0;
		return ;
	}
	else if (type == 1)
	{
		philo->philo_id = i;
		philo->meals_cnt = 0;
		philo->last_meal_time = 0;
		philo->is_full = 0;
		philo->table = table;
		return ;
	}
}
