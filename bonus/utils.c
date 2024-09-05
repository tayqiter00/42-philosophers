/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:17:22 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:03:00 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_exit(char *error_msg)
{
	printf("%s\n", error_msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief	This is a modified version of the standard atoi function that also
 * 			checks if trailing non-numeric characters exist. Returns 1 if the
 * 			string is a positive number (long not int), 0 otherwise.
 * 
 * @param	str represents a specific argv input from the terminal. For instance,
 * 			argv[1] is a string which represents the num of philosophers.
*/

long ft_atol(char *str)
{
    size_t i;
    long sign;
    long result;

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
 * @brief	This is a function which returns how many milliseconds have passed since
 * 			1st Jan 1970. It utilizes the gettimeofday function from <sys/time.h>.
 * 			The timeval structure specifies a time value in seconds and microseconds.
*/

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
void	sleep_ms(long milliseconds)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(500);
}

void	print_msg(char *str, t_data *data)
{
	long	time;
	
	sem_wait(data->msg_lock);
	if (check_death_declared() == TRUE)
	{
		sem_post(data->msg_lock);
		return ;
	}
	time = get_time_ms() - data->start_time;
	printf("%ld %ld %s\n", time, data->id, str);
	sem_post(data->msg_lock);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	buffer = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!buffer)
		return (NULL);
	while (s1[i])
		buffer[j++] = s1[i++];
	i = 0;
	while (s2[i])
		buffer[j++] = s2[i++];
	buffer[j] = '\0';
	return (buffer);
}
static size_t	int_len(long n)
{
	size_t	count;

	count = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_ltoa(long n)
{
	size_t	len;
	long	nbr;
	char	*buffer;

	nbr = n;
	len = int_len(n);
	if (n < 0)
	{
		nbr *= -1;
		len++;
	}
	buffer = (char *)malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (0);
	buffer[len] = '\0';
	while (len--)
	{
		buffer[len] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (n < 0)
		buffer[0] = '-';
	return (buffer);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			break ;
		}
		i++;
	}
	return (s1[i] - s2[i]);
}
