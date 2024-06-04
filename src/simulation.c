/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:58:04 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/30 16:14:12 by plashkar         ###   ########.fr       */
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
	while (!get_int(table->table_mutex, &table->all_thread_ready))
		ft_mysleep(10, table);
}

/**
 * @brief It desyncronizes the philosophers so there isn't a lot of contention
 * for the forks. It uses a formula to get the optimal time to think.
 * if the philos are even, it sleeps for 30ms, otherwise it sleeps for the
 * optimal time to think * a random number between 0 and 1.
*/
void	desync_philos(t_philos *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	time_to_eat = philo->table->time_to_eat * 1000;
	time_to_sleep = philo->table->time_to_sleep * 1000;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	if (philo->table->philo_cnt % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			ft_mysleep(30, philo->table);
	}
	else
	{
		ft_mysleep(time_to_think * 0.42, philo->table);
	}
}

/**
 * @brief the philo routine.
 * 1. starts with a spinlock until all the philos have started running.
 * 2. sets the last meal time needed later by monitor to check if the
 *    philo staved to death or not. It increments the philo_active_cnt to keep
 *    track of the number of philos that are now running, this is needed for
 *    syncronization of the monitor thread.
 * 3. It then desyncronizes the philos to decrease the ammount of contention
 * 4. enters a while loop that will keep running until the simulation is over.
 *    This is the main loop where it checks if the philo is full or not in the
 *    beginning of the loop. then it eats, sleeps and thinks.
 * @param data the philo struct.
 * @return void
*/
void	*dinner_routine(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	wait_for_all_threads_start(philo->table);
	set_long(philo->mutex, &philo->last_meal_time, get_time(GET_TIME_MILLISEC));
	increment_long(philo->table->table_mutex, &philo->table->philo_active_cnt);
	desync_philos(philo);
	while (is_sim_finished(philo->table) == 0)
	{
		if (get_int(philo->mutex, &philo->is_full))
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

/**
 * @brief the lonely philo routine.
 * This is a special case for when there is only one philo.
 * He will eventually die of starvation.
 * @return void
*/
void	*lonely_dinner_routine(void *data)
{
	t_philos	*sad_philo;

	sad_philo = (t_philos *)data;
	wait_for_all_threads_start(sad_philo->table);
	set_long(sad_philo->mutex, &sad_philo->last_meal_time, \
	get_time(GET_TIME_MILLISEC));
	increment_long(sad_philo->table->table_mutex, \
	&sad_philo->table->philo_active_cnt);
	write_status(TAKEN_FIRST_FORK, sad_philo, DEBUG);
	while (!is_sim_finished(sad_philo->table))
		usleep(200);
	return (NULL);
}

/**
 * @brief The main simulation function.
 * 1. It creates threads for each philosopher and starts the simulation.
 * if there is only one philo, creates the thread with the lonely_dinner_routine.
 * else it will create threads for each philo and start the dinner_routine.
 * 2. it sets the start_time in the table struct.
 * 3. then it creates the monitor thread.
 * 4. waits for all the threads to finish.
 * 5. if all threads join, that means the simulation is over, so it sets
 *    the flag for the end of the simulation in thread safe way.
 * 6. Finally it joins the monitor thread and writes the dinner check.
 * @param table the main struct holding all the data for the simulation.
 * @return int 1 if error, 0 if success.
*/
int	start_simulation(t_simulation *table)
{
	int	i;

	i = -1;
	if (table->philo_cnt == 1)
		p_thread_op(THREAD_CREATE, table->philos[0].thread_id, \
		lonely_dinner_routine, &table->philos[0]);
	else
	{
		while (++i < table->philo_cnt)
			p_thread_op(THREAD_CREATE, table->philos[i].thread_id, \
			dinner_routine, &table->philos[i]);
	}
	table->start_time = get_time(GET_TIME_MILLISEC);
	set_int(table->table_mutex, &table->all_thread_ready, 1);
	p_thread_op(THREAD_CREATE, &table->monitor, monitor_routine, table);
	i = -1;
	while (++i < table->philo_cnt)
		p_thread_op(THREAD_JOIN, table->philos[i].thread_id, NULL, NULL);
	set_int(table->table_mutex, &table->end_of_simulation, 1);
	p_thread_op(THREAD_JOIN, &table->monitor, NULL, NULL);
	write_dinner_check(table, DEBUG);
	return (0);
}
