/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:36:52 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:25:03 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	Checks if the state of the simulation have been set to FALSE by
 * 			the waiter thread. 
*/

static	int	check_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->simulation == FALSE)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (END_SIMULATION);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (CONTINUE_SIMULATION);
}

/**
 *	@brief	Philosophers are synchronized further by forks (mutexes). Once
 			they pick up two forks, they'll start eating for the specified
			amount of time and put down their forks.
*/

static void	philo_eat(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		sleep_ms(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo);
	print_msg(EAT, philo);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time_ms();
	philo->is_eating = TRUE;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	sleep_ms(philo->time_to_eat);
	philo->is_eating = FALSE;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
/**
 * @brief	Prints "is sleeping" on the terminal at the specified timestamp.
 * 			Then sleeps for a specified period of time.
*/

static void	philo_sleep(t_philo *philo)
{
	print_msg("is sleeping", philo);
	sleep_ms(philo->time_to_sleep);
}

/**
 * @brief	Prints "is thinking" on the terminal at the specified timestamp
*/

static void	philo_think(t_philo *philo)
{
	print_msg("is thinking", philo);
}

/**
 * @brief	Each philosopher thread will call this function. Philo's last_meal
 * 			time is re-initialized here to reduce unwanted delays when num of
 * 			philos is big. Philosophers are manually synchronised by delaying
 * 			the philosophers with even IDs by a short period of time. This also
 * 			prevent deadlocks from happening. While the state of simulation is
 * 			TRUE, philosophers will alternate between eating, sleeping and
 * 			thinking states.
*/

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->meal_lock);
	if (philo->id % 2 == 0)
		sleep_ms(philo->time_to_eat - 10);
	while (check_simulation(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (arg);
}
