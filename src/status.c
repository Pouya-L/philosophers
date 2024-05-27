/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:25:33 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/27 19:52:38 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_fortune_cookie(void)
{
	char	**messages;
	// int		index;

	messages = (char *[]){
		"| Run!\t\t\t\t\t\t\t|",
		"Something will happen soon.",
		"You will meet someone important.",
		"A great opportunity is waiting for you.",
		"Your hard work will pay off soon.",
		"You will find what you've been looking for.",
		"You will have a long and healthy life.",
		"You will travel to many places."
		"Cheese."
		"Help, I'm being held prisoner in a chinese bakery."
	};


	// Get a random index
	// index = get_time(GET_TIME_MILLISEC) % 10;

	// Print the selected message
	printf("|-------------------------------------------------------|\n");
	printf("%s\n", messages[0]);
	printf("|-------------------------------------------------------|\n");

}

void	write_dinner_check(t_simulation *table, int	debug)
{
	long	i;
	long	j;

	i = 0;
	j = 0;
	if (debug == 0)
		return ;
	printf("|-------------------------------------------------------|\n");
	printf("| Simulation Data:\t\t\tServer : Pouya\t|\n");
	printf("|-------------------------------------------------------|\n");
	printf("| Philosopher Count: %ld\t\t\t\t\t|\n", table->philo_cnt);
	printf("| Time to Die: %ld ms\t\t\t\t\t|\n", table->time_to_die);
	printf("| Time to Eat: %ld ms\t\t\t\t\t|\n", table->time_to_eat);
	printf("| Time to Sleep: %ld ms\t\t\t\t\t|\n", table->time_to_sleep);
	printf("| Meals to Eat Full: %ld\t\t\t\t\t|\n", table->meals_to_eat_full);
	printf("|-------------------------------------------------------|\n");
	printf("| Philosopher Data:\t\t\t\t\t|\n");
	printf("| ID\tMeals Count\tLast meal time\tIs Full\t\t|\n");
	printf("|-------------------------------------------------------|\n");

	while (i < table->philo_cnt)
	{
		j += table->philos[i].meals_cnt;
		printf("| %d\t%d\t\t%ld\t\t%d\t\t|\n",
				table->philos[i].philo_id,
				table->philos[i].meals_cnt,
				(table->philos[i].last_meal_time - table->start_time),
				table->philos[i].is_full);
		i++;
	}
	printf("|-------------------------------------------------------|\n");
	printf("| Total meals: \t\t\t\t%ld\t\t|\n", j);
	printf("| Subtotal: \t\t\t\t%.2f\t€\t|\n", (j * 7.99) -  (((j * 7.99) * 0.23) / 1.23));
	printf("| IVA: \t\t\t\t\t%.2f\t€\t|\n", ((j * 7.99) * 0.23) / 1.23);
	printf("| Total: \t\t\t\t%.2f\t€\t|\n", (j * 7.99));
	printf("|-------------------------------------------------------|\n");
	print_fortune_cookie();
}

void	write_status_debug(t_philo_status status, t_philos *philo, long time)
{
	if (status == TAKEN_FIRST_FORK && !is_sim_finished(philo->table))
		printf("%ld %d has taken the first fork with the id %d🥇🍴\n", time, philo->philo_id, philo->first_fork->fork_id);
	else if (status == TAKEN_SECOND_FORK && !is_sim_finished(philo->table))
		printf("%ld %d has taken the second fork with the id %d🥈🍴\n", time, philo->philo_id, philo->second_fork->fork_id);
	else if (status == EATING && !is_sim_finished(philo->table))
	{
		printf("%ld %d is eating 😋🍽️\n", time, philo->philo_id);
		printf("philo %d has eaten %d meals\n", philo->philo_id, philo->meals_cnt);
	}
	else if (status == SLEEPING && !is_sim_finished(philo->table))
		printf("%ld %d is sleeping 😴💤💤\n", time, philo->philo_id);
	else if (status == THINKING && !is_sim_finished(philo->table))
		printf("%ld %d is thinking 🤔\n", time, philo->philo_id);
	else if (status == DIED && !is_sim_finished(philo->table))
		printf("💀💀💀 %ld %d died 💀💀💀\n", time, philo->philo_id);
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
