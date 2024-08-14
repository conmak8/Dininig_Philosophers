/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:42:24 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/14 02:27:35 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	single_philosopher_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	
	pthread_mutex_unlock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
}

void philosopher_eat(t_philosopher *philosopher) {
    int left_fork = philosopher->left_fork;
    int right_fork = philosopher->right_fork;
	
    // Ensure forks are locked in a consistent order
    if (left_fork < right_fork) {
    // if (philosopher->id % 2 != 0) {
        pthread_mutex_lock(&philosopher->sim_data->forks[left_fork]);
        log_status(philosopher, "has taken a fork");
        pthread_mutex_lock(&philosopher->sim_data->forks[right_fork]);
    } else {
        pthread_mutex_lock(&philosopher->sim_data->forks[right_fork]);
        log_status(philosopher, "has taken a fork");
        pthread_mutex_lock(&philosopher->sim_data->forks[left_fork]);
    }
	// philosopher->is_eating = true;
    log_status(philosopher, "has taken a fork");
	
    pthread_mutex_lock(&philosopher->last_meal_mutex);
    // philosopher->last_meal_time = get_current_time() + philosopher->sim_data->death_time;
    philosopher->last_meal_time = get_current_time();
	// printf("-------------get current time ------- %lld\n",(get_current_time()));
    pthread_mutex_unlock(&philosopher->last_meal_mutex);
    log_status(philosopher, "is eating");
    ft_msleep(philosopher->sim_data->eating_time);

    // Unlock in reverse order of locking
    // if (left_fork < right_fork) {
	// if (philosopher->id % 2 != 0) {
        pthread_mutex_unlock(&philosopher->sim_data->forks[right_fork]);
        pthread_mutex_unlock(&philosopher->sim_data->forks[left_fork]);
    // } else {
    //     pthread_mutex_unlock(&philosopher->sim_data->forks[right_fork]);
    //     pthread_mutex_unlock(&philosopher->sim_data->forks[left_fork]);
    // }
	// philosopher->is_eating = false;

	
    if (philosopher->sim_data->required_meals > 0)
	{
		pthread_mutex_lock(&philosopher->last_meal_mutex);
        philosopher->meals_count++;
		pthread_mutex_unlock(&philosopher->last_meal_mutex);
	}
}

// void philosopher_eat(t_philosopher *philosopher) {
// 	int left_fork = philosopher->left_fork;
// 	int right_fork = philosopher->right_fork;
// 	int lower_fork, higher_fork;

// 	// Determine the lower and higher numbered forks
// 	if (left_fork < right_fork) {
// 		lower_fork = left_fork;
// 		higher_fork = right_fork;
// 	} else {
// 		lower_fork = right_fork;
// 		higher_fork = left_fork;
// 	}

// 	// Lock the lower numbered fork first
// 	pthread_mutex_lock(&philosopher->sim_data->forks[lower_fork]);
// 	log_status(philosopher, "has taken a fork");
// 	pthread_mutex_lock(&philosopher->sim_data->forks[higher_fork]);
// 	log_status(philosopher, "has taken a fork");

// 	// Eating process
// 	pthread_mutex_lock(&philosopher->last_meal_mutex);
// 	philosopher->last_meal_time = get_current_time();
// 	pthread_mutex_unlock(&philosopher->last_meal_mutex);
// 	log_status(philosopher, "is eating");
// 	ft_msleep(philosopher->sim_data->eating_time);

// 	// Unlock in reverse order
// 	pthread_mutex_unlock(&philosopher->sim_data->forks[higher_fork]);
// 	pthread_mutex_unlock(&philosopher->sim_data->forks[lower_fork]);

// 	// Post-eating process
// 	if (philosopher->sim_data->required_meals > 0) {
// 		pthread_mutex_lock(&philosopher->last_meal_mutex);
// 		philosopher->meals_count++;
// 		pthread_mutex_unlock(&philosopher->last_meal_mutex);
// 	}
// }

int stop_simulation(t_sim_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop_simulation == 1)
		return (pthread_mutex_unlock(&data->stop_mutex), 1);
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->sim_data->num_philosophers == 1)
		return (single_philosopher_routine(philosopher), NULL);
	if (philosopher->id % 2 != 0)
	{
		log_status(philosopher, "is thinking");
		ft_msleep(philosopher->sim_data->eating_time);
	}
	while (!stop_simulation(philosopher->sim_data))
	{
		// pthread_mutex_lock(&philosopher->sim_data->stop_mutex);
		// if (philosopher->sim_data->stop_simulation)
		// 	return (pthread_mutex_unlock(&philosopher->sim_data->stop_mutex), NULL);
		// pthread_mutex_unlock(&philosopher->sim_data->stop_mutex);
		// if (philosopher->meals_count >= philosopher->sim_data->required_meals && 
		// 	philosopher->sim_data->required_meals != -1)
		// 	break;
		philosopher_eat(philosopher);
		if (stop_simulation(philosopher->sim_data))
			break ;
		log_status(philosopher, "is sleeping");
		ft_msleep(philosopher->sim_data->sleeping_time);
		if (stop_simulation(philosopher->sim_data))
			break ;
		log_status(philosopher, "is thinking");
	}
	return (NULL);
}
