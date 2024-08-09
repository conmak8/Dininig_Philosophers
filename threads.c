/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:02:34 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/09 02:25:28 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	launch_threads(t_sim_data *data, t_philosopher *philosophers)
{
	int i;
	pthread_t monitor_thread;

	printf("Creating threads...\n");

	// Launch the philosopher threads
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&philosophers[i].thread_id, NULL, &philosopher_routine, &philosophers[i]) != 0) {
			return (print_error("Failed to create philosopher thread"), 5);
		}
		i++;
	}

	// Launch a single monitor thread
	if (pthread_create(&monitor_thread, NULL, &monitor_philosophers, data) != 0) {
		return (print_error("Failed to create monitor thread"), 6);
	}

	// Join the philosopher threads
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_join(philosophers[i].thread_id, NULL) != 0) {
			return (print_error("Failed to join philosopher thread"), 7);
		}
		i++;
	}

	// Join the monitor thread
	if (pthread_join(monitor_thread, NULL) != 0) {
		return (print_error("Failed to join monitor thread"), 8);
	}

	return (1);
}

/* int	launch_threads(t_sim_data *data, t_philosopher *philosophers)
{
    int i;
    pthread_t monitor[data->num_philosophers];
    i = 0;
    printf("Creating threads...\n");
    
    // monitor_philosophers(philosophers);
    
    while (i < data->num_philosophers)
    {
        if (pthread_create(&monitor[i], NULL, &monitor_philosophers, &philosophers[i]) !=0)
            return (print_error("Failed to create Supervisor"), 4);
        if (pthread_create(&philosophers[i].thread_id, NULL, &philosopher_routine, &philosophers[i]) != 0) {
            return (print_error("Failed to create thread"), 5);
        }
        i++;
    }

    // monitor_philosophers(philosophers);
    
    printf("Joining threads...\n");
    i = 0; // Reset index to join threads
    while (i < data->num_philosophers)
    {
        if (pthread_join(monitor[i], NULL))
            return (print_error("Failed to join Supervisor thread"), 6);
        
        if (pthread_join(philosophers[i].thread_id, NULL) != 0) {
            return (print_error("Failed to join thread"), 6);
        }
        i++;
    }
    return (1);
} */