/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:57:13 by qtay              #+#    #+#             */
/*   Updated: 2024/07/07 17:02:56 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h> // printf
# include <unistd.h> // write, usleep, fork
# include <pthread.h> // pthread (create, mutex, join, detach)
# include <sys/time.h> // gettimeofday
# include <stdlib.h> // malloc, free, exit
// # include <string.h> // memset
# include <semaphore.h> // semaphores (open, close, post, wait, unlink)
# include <sys/wait.h> // waitpid
# include <signal.h> // kill


# define INIT_SUCCESS 0
# define MALLOC_FAILURE 1
# define MUTEX_INIT_FAILURE 1
# define FALSE 0
# define TRUE 1
# define CONTINUE_SIMULATION 1
# define END_SIMULATION 0
# define THREAD_SUCCESS 0
# define THREAD_FAILURE 1
# define EAT "\033[0;32mis eating\033[0m"
# define DIED "\033[0;31mdied\033[0m"
# define ARG_NUM_ERR "Error: Invalid number of arguments!"
# define ARG_SIGN_ERR "Error: Arguments must be positive numbers!"
# define DATA_INIT_ERR "Error: Data initialisation failed!"
# define FORK_INIT_ERR "Error: Fork initialisation failed!"
# define THREAD_ERROR "Error: Thread creation or joining failed!"

typedef	pthread_mutex_t	mutex;
typedef struct s_philo t_philo;

/**
 * 1. start_time		: Beginning of simulation
 * 2. simulation_state	: True when running, otherwise false
 * 3. action_lock		: Lock when changing data about eating meals or
 * 				   		  printing msg
 * 4. forks				: An array of forks
*/

typedef struct	s_data
{
	long		id;
	long		num_of_philos; //
	long		time_to_die; //
	long		time_to_eat; //
	long		time_to_sleep; //
	long		meals_to_eat; //
	long		meals_eaten; //
	long		start_time; //
	long		last_meal;
	int			is_eating; //
	// int			simulation; //
	sem_t		*philo_sem;
	sem_t		*msg_lock;
	sem_t		*forks;
	pthread_t	waiter;
} t_data;

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

// typedef struct s_philo
// {
// 	long		id;

// 	long		meals_eaten;
// 	long		start_time;
// 	long		last_meal;
// 	int			is_eating;
// 	int			simulation;
// 	sem_t		*philo;
// 	pid_t	process_id;
// 	t_data		*data;
// }	t_philo;


void	init_data(t_data *data, char **av);
void	dinner_table(t_data *data);
void	philo_routine(t_data *data, size_t id);
char	*ft_strjoin(char const *s1, char const *s2);

/* UTILITIES */
long ft_atol(char *str);
void	error_exit(char *error_msg);
long	get_time_ms(void);
void	sleep_ms(long milliseconds);
void	*waiter_routine(void *arg);
void	print_msg(char *str, t_data *data);
char	*ft_ltoa(long n);
int	check_death_declared(void);
int	ft_strcmp(char *s1, char *s2);
int	philo_should_die(t_data *data);
void	kill_philo(t_data *data);
void	philo_eat(t_data *data);
void	philo_sleep(t_data *data);
void	philo_think(t_data *data);
int	all_meals_eaten(t_data *data);
#endif