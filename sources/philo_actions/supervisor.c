/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:13:30 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/12 23:48:22 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*monitor_philosophers(void *arg)
{
	int			i;
	t_sim_data	*data ;
	int 		total_meals;

	data = (t_sim_data *)arg;
	total_meals = 0;

	usleep(5000);
	while (true)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			total_meals += data->philosophers[i].meals_count;
			pthread_mutex_lock(&data->last_meal_mutex);
			if ((data->required_meals * data->num_philosophers) >= total_meals) //---added this one
				return(pthread_mutex_unlock(&data->last_meal_mutex), NULL);
			if ((get_current_time() - data->philosophers[i].last_meal_time)
				> data->death_time)
			{
				pthread_mutex_unlock(&data->last_meal_mutex);
				// printf("%lld %d %s\n", (get_current_time() - data->start_time), data->philosophers[i].id, "died");
				log_status(data->philosophers, "died");
				pthread_mutex_lock(&data->stop_mutex);
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->last_meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
