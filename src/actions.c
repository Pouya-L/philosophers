/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:26:28 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/28 20:51:54 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief the philo eats and prints the status.
 * it uses the time_to_eat value from the table struct to eat.
 * it locks the forks before eating and unlocks them after eating.
 * it also updates the last_meal_time and meals_cnt
 * and checks if the philo is now full or not.
 * @param philo the philo struct to eat.
 * @return void
*/
void	philo_eat(t_philos *philo)
{
	mutex_op(MUTEX_LOCK, &philo->first_fork->fork);
	write_status(TAKEN_FIRST_FORK, philo, DEBUG);
	mutex_op(MUTEX_LOCK, &philo->second_fork->fork);
	write_status(TAKEN_SECOND_FORK, philo, DEBUG);

	set_long(philo->mutex, &philo->last_meal_time, get_time(GET_TIME_MILLISEC));
	philo->meals_cnt++;
	write_status(EATING, philo, DEBUG);
	ft_mysleep(philo->table->time_to_eat * 1000, philo->table);
	if (philo->table->meals_to_eat_full > 0 && philo->meals_cnt == \
	philo->table->meals_to_eat_full)
		set_int(philo->mutex, &philo->is_full, 1);
	mutex_op(MUTEX_UNLOCK, &philo->first_fork->fork);
	mutex_op(MUTEX_UNLOCK, &philo->second_fork->fork);
}

/**
 * @brief the philo sleeps and prints the status.
 * it uses the time_to_sleep value from the table struct to sleep.
 * @param philo the philo struct to sleep.
 * @return void
*/
void	philo_sleep(t_philos *philo)
{
	write_status(SLEEPING, philo, DEBUG);
	ft_mysleep(philo->table->time_to_sleep * 1000, philo->table);
}

/**
 * STILL TO BE WORKED ON
 * @brief the philo thinks and prints the status.
 * @param philo the philo struct to think.
*/
void	philo_think(t_philos *philo)
{
	write_status(THINKING, philo, DEBUG);
	return ;
}
