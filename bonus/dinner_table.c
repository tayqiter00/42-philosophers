/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:47:31 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 11:59:21 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	dinner_table(t_data *data)
{
	int		i;
	pid_t	process_id;

	i = -1;
	data->start_time = get_time_ms();
	while (++i < data->num_of_philos)
	{
		process_id = fork();
		if (process_id == 0)
			philo_routine(data, i + 1);
	}
	while (waitpid(0, NULL, 0) != -1)
		;
}
