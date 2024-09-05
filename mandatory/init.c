/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:05:11 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:26:29 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	This function initialises elements of the t_data struct that was
 * 			declared earlier (mutex init and malloc).
*/

int	init_data(t_data *data, char **av)
{
	data->start_time = get_time_ms();
	data->simulation = TRUE;
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (MUTEX_INIT_FAILURE);
	if (pthread_mutex_init(&data->msg_lock, NULL))
		return (MUTEX_INIT_FAILURE);
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (MUTEX_INIT_FAILURE);
	data->forks = malloc(sizeof(t_mutex) * ft_atol(av[1]));
	if (!data->forks)
		return (MALLOC_FAILURE);
	data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!data->philos)
		return (MALLOC_FAILURE);
	return (INIT_SUCCESS);
}

/**
 * @brief	This function initialises the forks (mutexes) contained in the
 * 			t_data struct.
*/

int	init_forks(t_data *data, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atol(av[1]))
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (MUTEX_INIT_FAILURE);
	}
	return (INIT_SUCCESS);
}

/**
 * @brief	This function initialises the t_philo struct which represents
 * 			each individual philosopher.
*/

void	init_philos(t_data *data, char **av)
{
	int		i;
	long	num_of_philos;

	i = -1;
	num_of_philos = ft_atol(av[1]);
	while (++i < num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].num_of_philos = num_of_philos;
		data->philos[i].time_to_die = ft_atol(av[2]);
		data->philos[i].time_to_eat = ft_atol(av[3]);
		data->philos[i].time_to_sleep = ft_atol(av[4]);
		data->philos[i].meals_to_eat = -1;
		if (av[5] != NULL)
			data->philos[i].meals_to_eat = ft_atol(av[5]);
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_ms();
		data->philos[i].is_eating = FALSE;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % num_of_philos];
		data->philos[i].data = data;
	}
}
