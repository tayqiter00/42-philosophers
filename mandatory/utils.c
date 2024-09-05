/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:59:05 by qtay              #+#    #+#             */
/*   Updated: 2024/09/04 18:15:45 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	This is a modified version of the standard atoi function that also
 * 			checks if trailing non-numeric characters exist. Returns 1 if the
 * 			string is a positive number (long not int), 0 otherwise.
 * 
 * @param	str represents a specific argv input from the terminal. For instance,
 * 			argv[1] is a string which represents the num of philosophers.
*/

long	ft_atol(char *str)
{
	size_t	i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
    		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
    	result = (result * 10) + (str[i++] - '0');
	if (str[i])
		return (0);
	return (sign * result);
}

/**
 * @brief	This is a function which returns how many milliseconds have passed
 * 			since 1st Jan 1970. It utilises the gettimeofday() function from
 * 			<sys/time.h>. The timeval structure specifies a time value in seconds
 * 			and microseconds.
*/

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief	This function prints the state of each philosopher at specified
 * 			timestamps. Before printing, it checks the simulation state which
 * 			requires a mutex. Another mutex is also used before actually printing
 * 			even though the printf() function is thread safe to prevent from
 * 			getting a scrambled view.
 * 
 * @param	str the message to be printed
 * 
 * @param	philos each individual philosopher thread
*/

void	print_msg(char *str, t_philo *philos)
{
	long	time;

	pthread_mutex_lock(&philos->data->msg_lock);
	time = get_time_ms() - philos->data->start_time;
	pthread_mutex_lock(&philos->data->death_lock);
	if (philos->data->simulation == TRUE)
		printf("%ld %ld %s\n", time, philos->id, str);
	pthread_mutex_unlock(&philos->data->death_lock);
	pthread_mutex_unlock(&philos->data->msg_lock);
}

/**
 * @brief	The usleep() system call is inaccurate as it sleeps for AT LEAST
 * 			the specified time. Here, we make it more accurate to a millsecond-
 * 			level and also changing its argument to milliseconds from
 * 			microseconds.
 * 
 * @param	milliseconds desired sleep time in milliseconds
*/

void	sleep_ms(long milliseconds)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(500);
}
