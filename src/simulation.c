/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:58:04 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/22 18:24:09 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief waits for all the threads to start before starting the simulation.
 * It used a spin lock method to keep "waiting" in a while loop until
 * the all_threads_ready flag in the table struct is set to 1.
 * It uses a thread safe getter function to get the value of the flag.
 * @param table the main struct holding all the data for the simulation.
 * @return void
*/
void	wait_for_all_threads_start(t_simulation *table)
{
	while(!get_int(table->table_mutex, &table->all_thread_ready))
		;
}

void	*dinner_routine(void *data)
{
	t_philos *philo;

	philo = (t_philos *)data;
	wait_for_all_threads_start(philo->table);
	increment_long(philo->table->table_mutex, &philo->table->philo_active_cnt);

	//set last meal time

	//maine while loop
	while (is_sim_finished(philo->table) == 0)
	{
		//am i full might need to change it and make it threadsafe
		if (philo->is_full)
			break ;

		//eat
		philo_eat(philo);

		//sleep we need to write a precise usleep and wirte the sattus
		philo_sleep(philo);

		//think
		philo_think(philo);
	}
	return (NULL);
}

/**
 *
 * what should this function do?
 * ./philo 5 800 200 200 [5]
 *
 * if [5] is not provided, it should be -1 however if its zero then the simulation\
 * should not run
 *
 * if only one philo, a special function
 *
 * create all the threads
 *
 * monitor all the threads and the monitor function should find out
 * if a philo is dead or not as ASAP
 *
 * synronize the begging of the strads they should run simulatounsly
 *
 * finally join everyone
 *
 * @brief The main simulation function. It creates threads for each philosopher
 * and starts the simulation.
 * @param table the main struct holding all the data for the simulation.
 * @return int 1 if error, 0 if success.
*/
int	start_simulation(t_simulation *table)
{
	int	i;

	i = -1;
	// if (table->philo_cnt == 1)
	// 	//ad_hoc_function for only one philo
	while (++i < table->philo_cnt)
	{
		p_thread_op(THREAD_CREATE, table->philos[i].thread_id, dinner_routine, &table->philos[i]);
	}


	//start of simulation
	table->start_time = get_time(GET_TIME_MILLISEC);
	set_int(table->table_mutex, &table->all_thread_ready, 1);

	//creating and staring the monitor thread
	p_thread_op(THREAD_CREATE, table->monitor, monitor_routine, table)
	// join all thread
	i = -1;
	while (++i < table->philo_cnt)
	{
		p_thread_op(THREAD_JOIN, table->philos[i].thread_id, NULL, NULL);
	}
	set_int(table->table_mutex, &table->end_of_simulation, 1);
	return (0);
}
