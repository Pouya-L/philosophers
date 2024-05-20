/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:58:04 by plashkar          #+#    #+#             */
/*   Updated: 2024/05/20 11:01:13 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
