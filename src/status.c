/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:25:33 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/22 17:31:25 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status_debug(t_philo_status status, t_philos *philo, long time)
{
	if (status == TAKEN_FIRST_FORK && !is_sim_finished(philo->table))
		printf("%ld %d has taken the first fork with the id %d🥇🍴\n", time, philo->philo_id, philo->first_fork->fork_id);
	else if (status == TAKEN_SECOND_FORK && !is_sim_finished(philo->table))
		printf("%ld %d has taken the second fork with the id %d🥈🍴\n", time, philo->philo_id, philo->second_fork->fork_id);
	else if (status == EATING && !is_sim_finished(philo->table))
	{
		printf("%ld %d is eating 😋🍽️\n", time, philo->philo_id);
		printf("philo %d has eaten %d meals\n", philo->philo_id ,philo->meals_cnt);
	}
	else if (status == SLEEPING && !is_sim_finished(philo->table))
		printf("%ld %d is sleeping 😴💤💤\n", time, philo->philo_id);
	else if (status == THINKING && !is_sim_finished(philo->table))
		printf("%ld %d is thinking 🤔\n", time, philo->philo_id);
	else if (status == DIED && !is_sim_finished(philo->table))
		printf("💀💀💀 %ld %d died 💀💀💀", time, philo->philo_id);
}

void	write_status(t_philo_status status, t_philos *philo, int debug)
{
	long	elapsed_time;

	if(philo->is_full) //may need to put a mutex
		return ;

	mutex_op(MUTEX_LOCK, philo->table->write_mutex);
	elapsed_time = get_time(GET_TIME_MILLISEC) - philo->table->start_time;
	if (debug)
		write_status_debug(status, philo, elapsed_time);
	else
	{
		if ((status == TAKEN_FIRST_FORK || status == TAKEN_SECOND_FORK) && !is_sim_finished(philo->table))
			printf("%ld %d has taken a fork\n", elapsed_time, philo->philo_id);
		else if (status == EATING && !is_sim_finished(philo->table))
			printf("%ld %d is eating\n", elapsed_time, philo->philo_id);
		else if (status == SLEEPING && !is_sim_finished(philo->table))
			printf("%ld %d is sleeping\n", elapsed_time, philo->philo_id);
		else if (status == THINKING && !is_sim_finished(philo->table))
			printf("%ld %d is thinking\n", elapsed_time, philo->philo_id);
		else if (status == DIED && !is_sim_finished(philo->table))
			printf("%ld %d died\n", elapsed_time, philo->philo_id);
	}
	mutex_op(MUTEX_UNLOCK, philo->table->write_mutex);
}
