/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:02:34 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/10 02:06:52 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_threads(t_sim_data *data, t_philosopher *philosophers)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&philosophers[i].thread_id, NULL, \
		&philosopher_routine, &philosophers[i]) != 0)
			return (print_error("Failed to create philosopher thread"), 5);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor_philosophers, data) != 0)
		return (print_error("Failed to create monitor thread"), 6);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_join(philosophers[i].thread_id, NULL) != 0)
			return (print_error("Failed to join philosopher thread"), 7);
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (print_error("Failed to join monitor thread"), 8);
	return (1);
}

int	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}
