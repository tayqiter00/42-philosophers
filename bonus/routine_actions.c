/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:27:02 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:02:59 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_data *data)
{
	if (data->num_of_philos == 1)
	{
		sleep_ms(data->time_to_die);
		return ;
	}
	sem_wait(data->forks);
	print_msg("has taken a fork", data);
	sem_wait(data->forks);
	print_msg("has taken a fork", data);
	print_msg("is eating", data);
	data->last_meal = get_time_ms();
	data->is_eating = TRUE;
	data->meals_eaten++;
	sleep_ms(data->time_to_eat);
	data->is_eating = FALSE;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_sleep(t_data *data)
{
	if (check_death_declared() == TRUE)
		return ;
	print_msg("is sleeping", data);
	sleep_ms(data->time_to_sleep);
}

void	philo_think(t_data *data)
{
	if (check_death_declared() == TRUE)
		return ;
	print_msg("is thinking", data);
}
