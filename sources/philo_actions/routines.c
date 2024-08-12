/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:42:24 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/12 20:35:15 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	single_philosopher_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->print_mutex);
	philosopher->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
	pthread_mutex_unlock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
}

void philosopher_eat(t_philosopher *philosopher) {
    int left_fork = philosopher->left_fork;
    int right_fork = philosopher->right_fork;

    // Ensure forks are locked in a consistent order
    if (left_fork < right_fork) {
        pthread_mutex_lock(&philosopher->sim_data->forks[left_fork]);
        log_status(philosopher, "has taken a fork");
        pthread_mutex_lock(&philosopher->sim_data->forks[right_fork]);
    } else {
        pthread_mutex_lock(&philosopher->sim_data->forks[right_fork]);
        log_status(philosopher, "has taken a fork");
        pthread_mutex_lock(&philosopher->sim_data->forks[left_fork]);
    }

    log_status(philosopher, "has taken a fork");
    pthread_mutex_lock(&philosopher->sim_data->last_meal_mutex);
    philosopher->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philosopher->sim_data->last_meal_mutex);
    log_status(philosopher, "is eating");
    ft_msleep(philosopher->sim_data->eating_time);

    // Unlock in reverse order of locking
    if (left_fork < right_fork) {
        pthread_mutex_unlock(&philosopher->sim_data->forks[right_fork]);
        pthread_mutex_unlock(&philosopher->sim_data->forks[left_fork]);
    } else {
        pthread_mutex_unlock(&philosopher->sim_data->forks[left_fork]);
        pthread_mutex_unlock(&philosopher->sim_data->forks[right_fork]);
    }

    if (philosopher->sim_data->required_meals > 0)
        philosopher->meals_count++;
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
	
	while (true)  													//if i dd supervisor this will be data race.		
	{
		pthread_mutex_lock(&philosopher->sim_data->stop_mutex);
		if (philosopher->sim_data->stop_simulation)
			return (pthread_mutex_unlock(&philosopher->sim_data->stop_mutex), NULL);
		pthread_mutex_unlock(&philosopher->sim_data->stop_mutex);
		if (philosopher->meals_count >= philosopher->sim_data->required_meals && \
			philosopher->sim_data->required_meals != 0)
			break;
		philosopher_eat(philosopher);
		log_status(philosopher, "is sleeping");
		ft_msleep(philosopher->sim_data->sleeping_time);
		log_status(philosopher, "is thinking");
	}
	return (NULL);
}
