/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:51:30 by qtay              #+#    #+#             */
/*   Updated: 2024/09/05 16:45:49 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	This is the first helper function of the waiter_routine() function.
 * 			It checks if any philosophers have starved by comparing their last
 * 			meal time (counted from the beginning of last meal or start of
 * 			simulation) with the time elapsed. It sets the state of the
 * 			simulation to FALSE in the case where a philospher should die,
 * 			indicating that the simulation should come to a halt.
 * 
 * @param	philos is the t_philo array which allows the check_death()
 * 			function to have access to all philos easily
*/
static int	check_death(t_philo	*philos)
{
	int		i;

	i = -1;
	while (++i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(&philos->data->meal_lock);
		if (get_time_ms() - philos[i].last_meal >= philos->time_to_die
			&& philos[i].is_eating == FALSE)
		{
			pthread_mutex_unlock(&philos->data->meal_lock);
			print_msg(DIED, philos);
			pthread_mutex_lock(&philos->data->death_lock);
			philos->data->simulation = FALSE;
			pthread_mutex_unlock(&philos->data->death_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&philos->data->meal_lock);
		usleep(10);
	}
	return (FALSE);
}

/**
 * @brief	This is the second helper function. Its function is similar to the
 * 			check_death() function but instead it checks if the number of meals
 * 			each philosopher must eat is reached. If true, it sets the
 * 			simulation state to FALSE.
 * 
 * @param	philos is the t_philo array which allows the all_meals_eaten()
 * 			function to have access to all philos easily
*/
static int	all_meals_eaten(t_philo	*philos)
{
	int		i;
	long	count;

	i = -1;
	count = 0;
	if (philos->meals_to_eat == -1)
		return (FALSE);
	while (++i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(&philos->data->meal_lock);
		if (philos[i].meals_eaten >= philos->meals_to_eat)
			count++;
		pthread_mutex_unlock(&philos->data->meal_lock);
	}
	if (count == philos[0].num_of_philos)
	{
		pthread_mutex_lock(&philos->data->death_lock);
		philos->data->simulation = FALSE;
		pthread_mutex_unlock(&philos->data->death_lock);
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief	This function is called by the waiter thread. Its function is to
 * 			check if any philosophers have died or if the number of meals each
 * 			philosopher must eat is reached. If either is true, it breaks out
 *			of its infinite while loop.
 *
 * @param	arg will be type casted to (t_philo *) which represents the t_philo
 *			array
*/
void	*waiter_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
		if (check_death(philos) || all_meals_eaten(philos))
			break ;
	return (arg);
}
