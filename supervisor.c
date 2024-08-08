/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:13:30 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/09 00:55:11 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philosophers(void *arg)
{
	int	i;

	t_philosopher	*philosopher;
	philosopher = (t_philosopher *)arg;
	
	while (1)
	{
		i = 0;
		while (i < philosopher[0].sim_data->num_philosophers)
		{
			if (get_current_time() - philosopher[i].last_meal_time > philosopher[0].sim_data->death_time)
			{
				log_status(&philosopher[i], "died");
				philosopher[0].sim_data->stop_simulation = 1;
				break ;
			}
			i++;
		}
		if (philosopher[0].sim_data->stop_simulation)
			break ;
		usleep(1000);
	}
	return(NULL);
}
