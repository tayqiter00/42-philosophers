/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:47:20 by qtay              #+#    #+#             */
/*   Updated: 2024/09/05 16:36:54 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	This function is where the dining philosophers simulation begins.
 * 			A waiter thread is first created to monitor the state of the
 * 			philosophers. The philosopher threads are then created which runs
 * 			the simulation indefinitely by calling the philo_routine() function
 * 			until a philosopher dies or the number of meals each philosopher
 * 			must eat is reached. When the simulation ends, the pthread_join()
 * 			function is called for each thread. This ensures the main thread
 * 			waits for the waiter and philosopher threads to finish before
 * 			continuing. It also ensures resources used by the threads will be
 * 			properly cleaned up.
*/
int	dinner_table(t_data *data)
{
	int			i;
	pthread_t	waiter;

	i = -1;
	if (pthread_create(&waiter, NULL, &waiter_routine, data->philos) != 0)
		return (THREAD_FAILURE);
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (THREAD_FAILURE);
	}
	if (pthread_join(waiter, NULL) != 0)
		return (THREAD_FAILURE);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (THREAD_FAILURE);
	}
	return (THREAD_SUCCESS);
}
