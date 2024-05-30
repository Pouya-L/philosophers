/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:00:31 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 11:08:34 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief destroys the forks and frees the memory allocated for them.
 * Will only be called if the program fails in the middle of initing the forks.
 * @param table the main struct holding all the data for the simulation.
 * @param i the index of the fork to start destroying from.
 * @return 1 on success.
*/
int	destroy_fork_init(t_simulation *table, int i)
{
	while (i >= 0)
	{
		mutex_op(MUTEX_DESTROY, &table->forks[i].fork);
		i--;
	}
	return (1);
}

/**
 * @brief assigns the forks to the philos.
 * @param philo the philo struct to assign the forks to.
 * @param philo_pos the position of the philo in the philos array.
 * @param forks the array of forks.
 * @return void
*/
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
 * @brief sets up the philos struct with the necessary data.
 * If it fails on any of the steps, it will print an error message.
 * @param table the main struct holding all the data for the simulation.
 * @return 0 on success, 1 on failure.
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
	if (mutex_op(MUTEX_INIT, table->write_mutex))
		return (1);
	return (0);
}

/**
 * @brief initializes the data for the simulation.
 * If it fails on any of the steps, it will print an error message.
 * @param table the main struct holding all the data for the simulation.
 * @return 0 on success, 1 on failure.
*/
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
