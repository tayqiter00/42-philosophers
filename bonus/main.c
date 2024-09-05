/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:57:15 by qtay              #+#    #+#             */
/*   Updated: 2024/07/05 18:26:25 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief	Checks if all command line arguments are positive numbers.
 * 			It utilises a modified ft_atol function to do this.
*/

static int all_positive_nums(char **av)
{
    int     i;
    long    n;

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
		error_exit(ARG_NUM_ERR);
    if (!all_positive_nums(av))
		error_exit(ARG_SIGN_ERR);
	init_data(&data, av);
	dinner_table(&data);
	return (EXIT_SUCCESS);
}
