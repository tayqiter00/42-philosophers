/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:03:48 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 11:27:18 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_should_die(t_data *data)
{
	sem_wait(data->philo_sem);
	if (get_time_ms() - data->last_meal >= data->time_to_die
			&& data->is_eating == FALSE)
	{
		sem_post(data->philo_sem);
		return (TRUE);
	}
	sem_post(data->philo_sem);
	return (FALSE);
}
void	kill_philo(t_data *data)
{	
	sem_open("/death", O_CREAT, 0644, 0);
	// print_msg("died", data);
}

int	check_death_declared(void)
{
	sem_t	*death;

	death = sem_open("/death", AT_EACCESS, 0);
	if (death == SEM_FAILED)
		return (FALSE);
	sem_close(death);
	return (TRUE);
}

void	*waiter_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1) 
	{
		if (check_death_declared() == TRUE || all_meals_eaten(data) == TRUE)
			break ;
		if (philo_should_die(data) == TRUE)
		{
			sem_wait(data->msg_lock);
			if (philo_should_die(data) == TRUE && check_death_declared() == FALSE)
			{
				kill_philo(data);
				printf("%ld %ld %s\n", get_time_ms() - data->start_time, data->id, "died");
				sem_post(data->msg_lock);
				break ;
			}
			sem_post(data->msg_lock);
		}
	}
	return (arg);	
}
