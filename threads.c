/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:02:34 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 23:00:58 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_threads(t_sim_data *data, t_philosopher *philosophers)
{
    int i;

    i = 0;
    printf("Creating threads...\n");
    while (i < data->num_philosophers)
    {
        if (pthread_create(&philosophers[i].thread_id, NULL, &philosopher_routine, &philosophers[i]) != 0) {
            return (print_error("Failed to create thread"), 4);
        }
        i++;
    }

    printf("Joining threads...\n");
    i = 0; // Reset index to join threads
    while (i < data->num_philosophers)
    {
        if (pthread_join(philosophers[i].thread_id, NULL) != 0) {
            return (print_error("Failed to join thread"), 4);
        }
        i++;
    }
    return (1);
}
