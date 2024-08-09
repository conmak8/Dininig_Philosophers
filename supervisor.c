/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:13:30 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/09 02:47:22 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*monitor_philosophers(void *arg)
// {
// 	int	i;

// 	t_philosopher	*philosopher;
// 	philosopher = (t_philosopher *)arg;
	
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < philosopher[0].sim_data->num_philosophers)
// 		{
// 			if (get_current_time() - philosopher[i].last_meal_time > philosopher[0].sim_data->death_time)
// 			{
// 				log_status(&philosopher[i], "died");
// 				philosopher[0].sim_data->stop_simulation = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (philosopher[0].sim_data->stop_simulation)
// 			break ;
// 		usleep(1000);
// 	}
// 	return(NULL);
// }


void *monitor_philosophers(void *arg)
{
    t_sim_data *data = (t_sim_data *)arg;
    int i;

    while (!data->stop_simulation)
    {
        i = 0;
        while (i < data->num_philosophers)
        {
            if (get_current_time() - data->philosophers[i].last_meal_time > data->death_time)
            {
                // log_status(&data->philosophers[i], "died");
				printf("%lld %d %s\n", (get_current_time() - data->start_time), data->philosophers[i].id, "died");
                data->stop_simulation = 1;
                break ;
            }
            i++;
        }
    }
    return(NULL);
}
