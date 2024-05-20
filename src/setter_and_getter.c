/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_and_getter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:45:02 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/20 12:17:03 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief sets the value of an int data item in a thread safe way.
 * @param mutex the mutex to lock and unlock.
 * @param dest_int the value to set.
 * @param value_to_set the value to set the data item to.
 * @return void
*/
void	set_int(pthread_mutex_t *mutex, int *dest_int, int value_to_set)
{
	mutex_op(MUTEX_LOCK, mutex);
	*dest_int = value_to_set;
	mutex_op(MUTEX_UNLOCK, mutex);
}

/**
 * @brief gets the value of an int data item in a thread safe way.
 * @param mutex the mutex to lock and unlock.
 * @param value the value to get.
 * @return int the value of the data item.
*/
int	get_int(pthread_mutex_t *mutex, int *value)
{
	int return_value;

	mutex_op(MUTEX_LOCK, mutex);
	return_value = *value;
	mutex_op(MUTEX_UNLOCK, mutex);
	return (return_value);
}

/**
 * @brief sets the value of a long data item in a thread safe way.
 * @param mutex the mutex to lock and unlock.
 * @param dest_long the value to set.
 * @param value_to_set the value to set the data item to.
 * @return void
*/
void	set_long(pthread_mutex_t *mutex, long *dest_long, long value_to_set)
{
	mutex_op(MUTEX_LOCK, mutex);
	*dest_long = value_to_set;
	mutex_op(MUTEX_UNLOCK, mutex);
}

/**
 * @brief gets the value of a long data item in a thread safe way.
 * @param mutex the mutex to lock and unlock.
 * @param value the value to get.
 * @return long the value of the data item.
*/
long	get_long(pthread_mutex_t *mutex, long *value)
{
	long return_value;

	mutex_op(MUTEX_LOCK, mutex);
	return_value = *value;
	mutex_op(MUTEX_UNLOCK, mutex);
	return (return_value);
}

int	is_sim_finished(t_simulation *table)
{
	return(get_int(table->table_mutex, &table->end_of_simulation));
}
