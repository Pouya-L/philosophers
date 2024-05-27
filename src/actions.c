/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:26:28 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/27 11:36:30 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


//grab the forks

//write that eating 2 update the last meal time 3 update meals cnt

//release the forks

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
	if (philo->table->meals_to_eat_full > 0 && philo->meals_cnt == philo->table->meals_to_eat_full)
		set_int(philo->mutex, &philo->is_full, 1);
	mutex_op(MUTEX_UNLOCK, &philo->first_fork->fork);
	mutex_op(MUTEX_UNLOCK, &philo->second_fork->fork);
}

void	philo_sleep(t_philos *philo)
{
	write_status(SLEEPING, philo, DEBUG);
	ft_mysleep(philo->table->time_to_sleep * 1000, philo->table);
}

void	philo_think(t_philos *philo)
{
	write_status(THINKING, philo, DEBUG);
	return ;
}
