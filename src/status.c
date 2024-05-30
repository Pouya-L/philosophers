/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:25:33 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/28 00:53:12 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status_debug(t_philo_status status, t_philos *philo, long time)
{
	if (status == TAKEN_FIRST_FORK && !is_sim_finished(philo->table))
		printf("%ld %d has taken the first fork with the id %d🥇🍴\n", \
		time, philo->philo_id, philo->first_fork->fork_id);
	else if (status == TAKEN_SECOND_FORK && !is_sim_finished(philo->table))
		printf("%ld %d has taken the second fork with the id %d🥈🍴\n", \
		time, philo->philo_id, philo->second_fork->fork_id);
	else if (status == EATING && !is_sim_finished(philo->table))
	{
		printf("%ld philo %d is eating 😋🍽️\n", time, philo->philo_id);
		printf("🍗 This philo has eaten %d meals 🍗\n", philo->meals_cnt);
	}
	else if (status == SLEEPING && !is_sim_finished(philo->table))
		printf("%ld %d is sleeping 😴💤💤\n", time, philo->philo_id);
	else if (status == THINKING && !is_sim_finished(philo->table))
		printf("%ld %d is thinking 🤔\n", time, philo->philo_id);
	else if (status == DIED && !is_sim_finished(philo->table))
		printf("💀 %s%ld %d %sdied!💀\n", RED, time, philo->philo_id, DEFAULT);
}

void	write_status(t_philo_status status, t_philos *philo, int debug)
{
	long	elapsed_time;

	if (get_int(philo->mutex, &philo->is_full))
		return ;
	mutex_op(MUTEX_LOCK, philo->table->write_mutex);
	elapsed_time = get_time(GET_TIME_MILLISEC) - philo->table->start_time;
	if (debug)
		write_status_debug(status, philo, elapsed_time);
	else
	{
		if ((status == TAKEN_FIRST_FORK || status == TAKEN_SECOND_FORK) && \
		!is_sim_finished(philo->table))
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

static void	print_check_top(t_simulation *table)
{
	printf("\n|-------------------------------------------------------|\n");
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
}

static void	print_fortune_cookie(void)
{
	char	**messages;
	int		index;

	messages = (char *[]){
		"| Dark humor is like food; not everyone gets it. \t|",
		"| Broken pencils are pointless...\t\t\t|",
		"| I used to be scared of hurdles, but I got over them.\t|",
		"| Inspecting mirrors is a job that\t\t\t|\n|\
		I could really see myself doing.\t|",
		"| When life gives you melons, you're dyslexic.\t\t|",
		"|\t\t\t  DON'T\t\t\t\t|\n|\t\t\t  PANIC.\t\t\t|",
		"| Error 404: Fortune not found.\t\t\t\t|",
		"| For external use only.\t\t\t\t|",
		"| A cardboard belt would be a waist of paper.\t\t|",
		"| Plan to be spontanous tomorrow.\t\t\t|",
		"| Whiteboards are remarkable.\t\t\t\t|",
		"| I used to be addicted to soap but I'm clean now.\t|",
		"| Para onde os gatos vão quando morrem?\t\t\t|\n|\
		 Para o purGATOrio.\t\t\t|",
		"| O que o martelo foi fazer na igreja? Ele foi pregar.\t|"
	};
	index = get_time(GET_TIME_MILLISEC) % 14;
	printf("|-------------------------------------------------------|\n");
	printf("%s\n", messages[index]);
	printf("|-------------------------------------------------------|\n");
}

void	write_dinner_check(t_simulation *table, int debug)
{
	long	i;
	long	j;

	i = -1;
	j = 0;
	if (debug == 0)
		return ;
	print_check_top(table);
	while (++i < table->philo_cnt)
	{
		j += table->philos[i].meals_cnt;
		printf("| %d\t%d\t\t%ld\t\t%d\t\t|\n",
			table->philos[i].philo_id,
			table->philos[i].meals_cnt,
			(table->philos[i].last_meal_time - table->start_time),
			table->philos[i].is_full);
	}
	printf("|-------------------------------------------------------|\n");
	printf("| Total meals: \t\t\t\t%ld\t\t|\n", j);
	printf("| Subtotal: \t\t\t\t%.2f\t€\t|\n", (j * 7.99) - \
	(((j * 7.99) * 0.23) / 1.23));
	printf("| IVA: \t\t\t\t\t%.2f\t€\t|\n", ((j * 7.99) * 0.23) / 1.23);
	printf("| Total: \t\t\t\t%.2f\t€\t|\n", (j * 7.99));
	printf("|-------------------------------------------------------|\n");
	print_fortune_cookie();
}
