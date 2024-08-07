/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:02:34 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 20:09:19 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_threads(t_sim_data *data, t_philosopher *philosophers)
{
	int i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if(!pthread_create(&philosophers[i].thread_id, NULL, (void**)philosophers_routine, &philosophers[i]))
			return (print_error("Failed to create thread"),4);
		i++;
	}

	while (i < data->num_philosophers)
	{
		if (!pthread_join(philosophers[i].thread_id, NULL))
			return (print_error("Failed to join thread"),4);
		i++;
	}

}