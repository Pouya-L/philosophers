/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:26:28 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 13:07:05 by plashkar         ###   ########.fr       */
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
 * @brief the philo thinks and prints the status. This is the only part
 * where we can actually influence the code and make it "fair" if the number
 * of philos is odd.
 * it uses the same formula as in desync_philos to calculate the time to think.
 * If the philo count is eveen it just returns since the system is already fair
 * however if the philo count is odd it sleeps for the optimal time to
 * think * a random number between 0 and 1.
 * @param philo the philo struct to think.
*/
void	philo_think(t_philos *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	time_to_eat = philo->table->time_to_eat * 1000;
	time_to_sleep = philo->table->time_to_sleep * 1000;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	write_status(THINKING, philo, DEBUG);
	if (philo->table->philo_cnt % 2 == 0)
		return ;
	ft_mysleep(time_to_think * 0.42, philo->table);
	return ;
}
