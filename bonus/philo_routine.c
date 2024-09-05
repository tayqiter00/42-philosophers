/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:56:22 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:02:57 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	all_meals_eaten(t_data *data)
{
	if (data->meals_to_eat == -1)
		return (FALSE);
	if (data->meals_eaten >= data->meals_to_eat)
		return (TRUE);
	else
		return (FALSE);
}

char	*create_sem_name(size_t id)
{
	return (ft_strjoin("/sem_", ft_ltoa(id)));
}

void	philo_set_up(t_data *data, size_t id)
{
	char	*philo_sem_name;

	data->id = id;
	philo_sem_name = create_sem_name(id);
	sem_unlink(philo_sem_name); // destroys the other sem created by another process
	data->philo_sem = sem_open(philo_sem_name, O_CREAT, 0644, 1); // might return EEXIST (O_EXCL)
	sem_unlink(philo_sem_name);
	free(philo_sem_name);
	sem_unlink("/death_lock");
	
	
	data->last_meal = get_time_ms();
}

void	philo_routine(t_data *data, size_t id)
{
	philo_set_up(data, id);
	if (id % 2 == 0)
		sleep_ms(data->time_to_eat - 10);
	pthread_create(&data->waiter, NULL, &waiter_routine, data);
	while (check_death_declared() == FALSE && all_meals_eaten(data) == FALSE)
	{
		philo_eat(data);
		philo_sleep(data);
		philo_think(data);
	}
	pthread_join(data->waiter, NULL);
	sem_close(data->philo_sem);
}
