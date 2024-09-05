/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:13:54 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 11:58:21 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	sem_unlink("/msg_lock");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_of_philos);
	data->msg_lock = sem_open("/msg_lock", O_CREAT, 0644, 1); // unused
	sem_unlink("/forks");
	sem_unlink("/msg_lock");
}

void	init_data(t_data *data, char **av)
{
	data->num_of_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	data->meals_to_eat = -1;
	if (av[5])
		data->meals_to_eat = ft_atol(av[5]);
	data->meals_eaten = 0;
	data->is_eating = FALSE;
	// data->simulation = TRUE;
	init_semaphores(data);
}
