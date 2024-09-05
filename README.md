# PHILOSOPHERS

## Mandatory part

### Mutexes used (locks)<br>
1. Meal lock<br>
`check_death()`:<br>
- Used by waiter thread to access `last_meal`, `time_to_die`, `is_eating`

`all_meals_eaten()`:<br>
- Used by waiter thread to access `meals_eaten`, `meals_to_eat`

`philo_eat()`:<br>
- Used by any philo thread to access `last_meal`, `is_eating`, `meals_eaten`

2. Message lock<br>
`print_msg()`:<br>
- to prevent scrambled view (not actually needed)

3. Death lock<br>
`check_death()`:<br>
- Used by waiter thread to access `simulation`

`all_meals_eaten()`:<br>
- Used by waiter thread to access `simulation`

`check_simulation()`:<br>
- Used by any philo thread to access `simulation` (can be removed though)

`print_msg()`:<br>
- Used by any philo thread to access `simulation`

4. Forks<br>
`philo_eat()`
- Used by any philo thread to access left and right forks