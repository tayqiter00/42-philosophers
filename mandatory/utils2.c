/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:42:40 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:10:23 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief	Destroys all philosophers' forks
*/

static void	destroy_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos[0].num_of_philos)
		pthread_mutex_destroy(&data->forks[i]);
}

/**
 * @brief	Destroys only the locks (not forks) and free all allocated
 * 			memory
*/

void	destroy_locks_n_free_mem(t_data *data)
{
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->msg_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->forks);
	free(data->philos);
}

/**
 * @brief	Destroys all locks and forks and free all allocated memory
*/

void	destroy_all_n_free_mem(t_data *data)
{
	destroy_forks(data);
	destroy_locks_n_free_mem(data);
}
