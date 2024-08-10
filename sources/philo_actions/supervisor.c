/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:13:30 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/10 04:06:48 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*monitor_philosophers(void *arg)
{
	int			i;
	int			total_meals_eaten;
	t_sim_data	*data ;

	data = (t_sim_data *)arg;
	while (!data->stop_simulation)
	{
		i = 0;
		total_meals_eaten = 0;
		while (i < data->num_philosophers)
		{
			if ((get_current_time() - data->philosophers[i].last_meal_time)
				> data->death_time)
			{
				// printf("%lld %d %s\n", (get_current_time() - data->start_time), data->philosophers[i].id, "died");
				log_status(data->philosophers, "died");
				data->stop_simulation = 1;
				break ;
			}
			total_meals_eaten += data->philosophers[i].meals_count;
			i++;
		}
		if (total_meals_eaten == (data->num_philosophers * data->required_meals))
			data->stop_simulation = 1;
	}
	return (NULL);
}
