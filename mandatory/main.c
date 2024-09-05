/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:57:15 by qtay              #+#    #+#             */
/*   Updated: 2024/09/05 16:37:08 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	Checks if all command line arguments are positive numbers.
 * 			It utilises a modified ft_atol function to do this.
*/
static int	all_positive_nums(char **av)
{
	int		i;
	long	n;

	i = 1;
	while (av[i])
	{
		n = ft_atol(av[i]);
		if (n <= 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief	Starts by parsing the input, initialising the data and running
 * 			the simulation. When the simulation ends, all mutexes are
 * 			destroyed and all heap memory is freed.
*/
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf(ARG_NUM_ERR), EXIT_FAILURE);
	if (!all_positive_nums(av))
		return (printf(ARG_SIGN_ERR), EXIT_FAILURE);
	if (init_data(&data, av))
	{
		destroy_locks_n_free_mem(&data);
		return (printf(DATA_INIT_ERR), EXIT_FAILURE);
	}
	if (init_forks(&data, av))
	{
		destroy_all_n_free_mem(&data);
		return (printf(FORK_INIT_ERR), EXIT_FAILURE);
	}
	init_philos(&data, av);
	if (dinner_table(&data))
	{
		destroy_all_n_free_mem(&data);
		return (printf(THREAD_ERROR), EXIT_FAILURE);
	}
	destroy_all_n_free_mem(&data);
	return (EXIT_SUCCESS);
}
