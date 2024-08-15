/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:42:24 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/15 03:22:22 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	single_philosopher_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->last_meal_mutex);
	philosopher->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philosopher->sim_data->last_meal_mutex);
	pthread_mutex_unlock \
	(&philosopher->sim_data->forks[philosopher->right_fork]);
}

void	philosopher_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->left_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->last_meal_mutex);
	philosopher->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philosopher->sim_data->last_meal_mutex);
	log_status(philosopher, "is eating");
	ft_msleep(philosopher->sim_data->eating_time);
	pthread_mutex_unlock
		(&philosopher->sim_data->forks[philosopher->right_fork]);
	pthread_mutex_unlock(&philosopher->sim_data->forks[philosopher->left_fork]);
	if (philosopher->sim_data->required_meals > 0)
	{
		pthread_mutex_lock(&philosopher->sim_data->last_meal_mutex);
		philosopher->meals_count++;
		pthread_mutex_unlock(&philosopher->sim_data->last_meal_mutex);
	}
}

int	stop_simulation(t_sim_data *data)
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
	pthread_mutex_lock(&philosopher->sim_data->start_mutex);
	philosopher->sim_data->ready_threads++;
	pthread_mutex_unlock(&philosopher->sim_data->start_mutex);
	while (1)
	{
		pthread_mutex_lock(&philosopher->sim_data->start_mutex);
		if (philosopher->sim_data->ready_threads == \
			philosopher->sim_data->num_philosophers)
		{
			pthread_mutex_unlock(&philosopher->sim_data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher->sim_data->start_mutex);
		usleep(100);
	}
	if (philosopher->sim_data->num_philosophers == 1)
		return (single_philosopher_routine(philosopher), NULL);
	routine_loop_in(philosopher);
	return (NULL);
}

void	routine_loop_in(t_philosopher *philosopher)
{
	if (philosopher->id % 2 != 0)
	{
		log_status(philosopher, "is thinking");
		ft_msleep(philosopher->sim_data->eating_time / 2);
	}
	while (!stop_simulation(philosopher->sim_data))
	{
		philosopher_eat(philosopher);
		if (stop_simulation(philosopher->sim_data))
			break ;
		log_status(philosopher, "is sleeping");
		ft_msleep(philosopher->sim_data->sleeping_time);
		if (stop_simulation(philosopher->sim_data))
			break ;
		log_status(philosopher, "is thinking");
		if (philosopher->sim_data->num_philosophers % 2 != 0)
			ft_msleep(2 * philosopher->sim_data->eating_time
				- philosopher->sim_data->sleeping_time);
	}
}
