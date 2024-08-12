/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:41:08 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/12 22:48:00 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}

void	log_status(t_philosopher *philosopher, char *status)
{
	pthread_mutex_lock(&philosopher->sim_data->stop_mutex);
	if (!philosopher->sim_data->stop_simulation)
	{
		pthread_mutex_unlock(&philosopher->sim_data->stop_mutex);
		pthread_mutex_lock(&philosopher->sim_data->print_mutex);
		printf("%lld %d %s\n", (get_current_time() - \
		philosopher->sim_data->start_time), philosopher->id, status);
		pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
		return;
	}
	pthread_mutex_unlock(&philosopher->sim_data->stop_mutex);
}

void	ft_msleep(long long msec)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < msec)
		usleep(200);
}
