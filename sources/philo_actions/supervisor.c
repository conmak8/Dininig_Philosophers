/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:13:30 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/14 01:26:11 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*monitor_philosophers(void *arg)
{
	int			i;
	t_sim_data	*data ;
	int 		philos_finished_meals;

	data = (t_sim_data *)arg;
	philos_finished_meals = 0;
	long long last_meal;

	// usleep(5000);
	// while (!stop_simulation(data))
	while (true)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			
			if ((data->required_meals != -1))
			{
				pthread_mutex_lock(&data->philosophers[i].last_meal_mutex);
				if (data->philosophers[i].meals_count == data->required_meals)
					philos_finished_meals++;
				pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
				// total_meals += data->philosophers[i].meals_count;
				// printf(" --- num philo = %d \n", data->num_philosophers);
				// printf(" --- req meals = %d \n", data->required_meals);
				// printf(" --- total meals = %d \n", total_meals);
				// printf(" --- * = %d \n", (data->required_meals * data->num_philosophers));
				
				if (philos_finished_meals == data->num_philosophers)
				{
					// printf(" --- total meals ------ = %d \n", total_meals);
					pthread_mutex_lock(&data->stop_mutex);
					data->stop_simulation = 1;
					pthread_mutex_unlock(&data->stop_mutex);
					return (NULL);
				}
			}
			pthread_mutex_lock(&data->philosophers[i].last_meal_mutex);
			last_meal = data->philosophers[i].last_meal_time;
			pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
			
			if ((get_current_time() - last_meal) > data->death_time)
			// if (!data->philosophers[i].is_eating && (get_current_time() >= data->death_time))
			{
				// printf("get current time ------- %lld\n",(get_current_time()));
				// printf("last meal time ------- %lld\n",(data->philosophers[i].last_meal_time) );
				// printf("time passed------- %lld\n",(get_current_time() - data->philosophers[i].last_meal_time) );
				// printf("death time------- %lld\n",(data->death_time) );
				
				// printf("%lld %d %s\n", (get_current_time() - data->start_time), data->philosophers[i].id, "died");
				log_status(&data->philosophers[i], "died");
				pthread_mutex_lock(&data->stop_mutex);
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
			// pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
			i++;
			// if (++i == data->num_philosophers)
			// 	i = 0;
		}
		usleep(1000);
	}
	return (NULL);
}
