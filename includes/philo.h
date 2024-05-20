/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:32 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/20 15:10:42 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>

//Color codes for ft_printf
# define DEFAULT "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"


typedef enum e_opcode
{
	MUTEX_INIT,
	MUTEX_LOCK,
	MUTEX_UNLOCK,
	MUTEX_DESTROY,
	THREAD_CREATE,
	THREAD_JOIN,
	THREAD_DETACH,
}	t_opcode;

typedef struct s_simulation t_simulation;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_forks;

typedef struct s_philos
{
	int				philo_id;
	int				meals_cnt;
	int				time_since_last_meal;
	int				is_full;
	t_forks			*first_fork;
	t_forks			*second_fork;
	pthread_t		*thread_id;
	t_simulation	*table;

}	t_philos;

struct s_simulation
{
	long				philo_cnt;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_to_eat_full;
	long				start_time;
	int					end_of_simulation;
	t_forks				*forks;
	t_philos			*philos;
	pthread_mutex_t		*table_mutex;
};

//utils
int		error_msg(char *msg);
long	ft_atol(const char *str);
long	ft_l_overflow_err(int sign);
int		check_args(char **argv, t_simulation *table);

//data init
int		mutex_op(t_opcode opcode, pthread_mutex_t *mutex);
int		p_thread_op(t_opcode opcode, pthread_t *thread, void *(*func)(void *), void *arg);
int		data_init(t_simulation *table);

//test functions
int		test_print_table_info(t_simulation *table);
void	test_print_fork_data(t_simulation *table);
void	test_print_philo_data(t_simulation *table);

//setter and getter
void	set_int(pthread_mutex_t *mutex, int *dest_int, int value_to_set);
int		get_int(pthread_mutex_t *mutex, int *value);
void	set_long(pthread_mutex_t *mutex, long *dest_long, long value_to_set);
long	get_long(pthread_mutex_t *mutex, long *value);

//clean up
int		free_everything(t_simulation *table);
void	free_forks(t_simulation *table);


#endif
