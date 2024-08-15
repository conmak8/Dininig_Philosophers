/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:13:30 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/15 04:43:42 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*monitor_philosophers(void *arg)
{
	int			i;
	t_sim_data	*data;
	int			philos_finished_meals;
	long long	last_meal;

	data = (t_sim_data *)arg;
	philos_finished_meals = 0;
	usleep(5000);
	while (true)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			if (monitor_meals_in_1(data, i, &philos_finished_meals))
				return (NULL);
			mon_lock_meal_2(data, i, &last_meal);
			if ((get_current_time() - last_meal) > data->death_time)
				return (mon_lock_meal_3(data, i), NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	mon_lock_meal_2(t_sim_data *data, int i, long long	*last_meal)
{
	pthread_mutex_lock(&data->last_meal_mutex);
	*last_meal = data->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&data->last_meal_mutex);
}

void	mon_lock_meal_3(t_sim_data *data, int i)
{
	log_status(&data->philosophers[i], "died");
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

bool	monitor_meals_in_1(t_sim_data *data, int i, int *philos_finished_meals)
{
	if ((data->required_meals != -1))
	{
		pthread_mutex_lock(&data->last_meal_mutex);
		if (data->philosophers[i].meals_count == data->required_meals
			&& !data->philosophers[i].finished)
		{
			data->philosophers[i].finished = 1;
			(*philos_finished_meals)++;
		}
		pthread_mutex_unlock(&data->last_meal_mutex);
		if (*philos_finished_meals == data->num_philosophers)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (true);
		}
	}
	return (false);
}
