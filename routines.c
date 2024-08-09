/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:42:24 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/09 13:48:50 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	single_philosopher_routine(t_philosopher *philosopher)
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

static void	philosopher_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->left_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	philosopher->last_meal_time = get_current_time();
	log_status(philosopher, "is eating");
	usleep(philosopher->sim_data->eating_time * 1000);												// grapse mia diki sou akriveia!!!---------------------
	pthread_mutex_unlock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
	pthread_mutex_unlock(&philosopher->sim_data->forks[philosopher->left_fork]);
	if (philosopher->sim_data->required_meals > 0)
	{
		pthread_mutex_lock(&philosopher->sim_data->print_mutex);
		philosopher->meals_count++;
		pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
	}
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
		usleep(philosopher->sim_data->eating_time * 500);
	}
	while (!philosopher->sim_data->stop_simulation)  													//if i dd supervisor this will be data race.		
	{
		philosopher_eat(philosopher);
		log_status(philosopher, "is sleeping");
		usleep(philosopher->sim_data->sleeping_time * 1000);
		log_status(philosopher, "is thinking");
	}
	return (NULL);
}
