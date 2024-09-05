/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:28:19 by qtay              #+#    #+#             */
/*   Updated: 2024/09/05 16:37:25 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <unistd.h> // write, usleep
# include <pthread.h> // pthread (create, mutex, join, detach)
# include <sys/time.h> // gettimeofday
# include <stdlib.h> // malloc, free

# define INIT_SUCCESS 0
# define MALLOC_FAILURE 1
# define MUTEX_INIT_FAILURE 1
# define FALSE 0
# define TRUE 1
# define CONTINUE_SIMULATION 1
# define END_SIMULATION 0
# define THREAD_SUCCESS 0
# define THREAD_FAILURE 1
# define ARG_NUM_ERR "Error: Invalid number of arguments!\n"
# define ARG_SIGN_ERR "Error: Arguments must be positive numbers!\n"
# define DATA_INIT_ERR "Error: Data initialisation failed!\n"
# define FORK_INIT_ERR "Error: Fork initialisation failed!\n"
# define THREAD_ERROR "Error: Thread creation or joining failed!\n"
# define EAT "\033[0;32mis eating\033[0m"
# define DIED "\033[0;31mdied\033[0m"

typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;

/**
 * 1. start_time		: Beginning of simulation
 * 2. simulation_state	: True when running, otherwise false
 * 3. action_lock		: Lock when changing data about eating meals or
 * 				   		  printing msg
 * 4. forks				: An array of forks
*/
typedef struct s_data
{
	long	start_time;
	int		simulation;
	t_mutex	death_lock;
	t_mutex	msg_lock;
	t_mutex	meal_lock;
	t_mutex	*forks;
	t_philo	*philos;
}	t_data;

/**
 * 1. 	id				: Each philosophers ID from 1 to num_of_philos
 * 2. 	num_of_philos	: Total number of philosophers
 * 3. 	time_to_die		: Philosophers will die after this amount of time
 * 						  passed from the start of last meal
 * 4. 	time_to_eat		: Time each philosopher will spend eating
 * 5. 	time_to_sleep	: Time each philosopher will spending sleeping
 * 6. 	last_meal		: Time stamp of when a philosopher's last meal was
 * 7.	is_eating		: True if a philosopher is currently eating, else false
 * 8.	left/right forks: Pointer to a specific fork inside t_data's array
 * 9. 	thread_id		: ID of each thread
 * 10.	data			: Pointer to the data struct
*/
typedef struct s_philo
{
	long		id;
	long		num_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_to_eat;
	long		meals_eaten;
	long		last_meal;
	int			is_eating;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

/* UTILITIES */
long	ft_atol(char *str);
long	get_time_ms(void);
void	destroy_mutexes(t_data *data);
void	sleep_ms(long milliseconds);
void	print_msg(char *str, t_philo *philos);

/* DINNER TABLE */
int		dinner_table(t_data *data);

/* WAITER ROUTINE */
void	*waiter_routine(void *arg);

/* INITIALISATION */
int		init_data(t_data *data, char **av);
int		init_forks(t_data *data, char **av);
void	init_philos(t_data *data, char **av);

/* PHILOSOPHER ROUTINE */
void	*philo_routine(void *arg);

/* UTILITIES */
void	destroy_locks_n_free_mem(t_data *data);
void	destroy_all_n_free_mem(t_data *data);

#endif