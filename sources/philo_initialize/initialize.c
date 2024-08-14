/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:52:40 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/14 23:31:13 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	initialize_data(int argc, char **argv, t_sim_data *data)
{
	data->num_philosophers = (int)ft_atoll(argv[1]);
	data->death_time = ft_atoll(argv[2]);
	data->eating_time = ft_atoll(argv[3]);
	data->sleeping_time = ft_atoll(argv[4]);
	if (argc == 6)
		data->required_meals = (int)ft_atoll(argv[5]);
	else
		data->required_meals = -1;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0 || pthread_mutex_init(&data->stop_mutex, NULL) != 0 \
	|| pthread_mutex_init(&data->last_meal_mutex, NULL) != 0 || pthread_mutex_init(&data->start_mutex, NULL) != 0) 
	{
		return (printf("Mutex initialization failed\n"), 0); //--------------pthread_mutex_destroy(&data->forks[i]) i don't need thiss
	}
	data->stop_simulation = 0;
	data->start_time = get_current_time();
	if (!init_philoshopers(data))
		return (0);
	data->ready_threads = 0;
	return (1);
}

int	init_philoshopers(t_sim_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!data->philosophers)
		return (print_error("Malloc Philo Failed\n"), ft_cleanup(data), 0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (print_error("Malloc Forks Failed\n"), ft_cleanup(data), 0);
	while (i < data->num_philosophers)
	{
		if (!init_philo_in(i, data))
			return (0);
		i++;
	}
	return (1);
}

int	init_philo_in(int i, t_sim_data *data)
{
	data->philosophers[i].thread_id = 0;
	data->philosophers[i].id = i + 1;
	data->philosophers[i].meals_count = 0;
	data->philosophers[i].finished = 0;
	// data->philosophers[i].is_eating = false;
	if (data->philosophers[i].id % 2 == 0)
	{
	// {right_fork
		data->philosophers[i].right_fork = i;
		data->philosophers[i].left_fork  = (i + 1) % data->num_philosophers;
	}
	else
	{
		data->philosophers[i].right_fork = (i + 1) % data->num_philosophers;
		data->philosophers[i].left_fork = i;
	}
	// data->philosophers[i].last_meal_time = get_current_time() + data->death_time;
	data->philosophers[i].last_meal_time = get_current_time();
	data->philosophers[i].sim_data = data;
	if (pthread_mutex_init(&data->forks[i], NULL) != 0 )
	// || pthread_mutex_init(&data->philosophers[i].last_meal_mutex, NULL) != 0 )
	{
		printf("Mutex initialization failed for fork %d\n", i);
		return (ft_cleanup(data), 0);
	}
	return (1);
}

void	ft_cleanup(t_sim_data *data)
{
	int	i;

	i = 0;
	if (data->philosophers)
		free(data->philosophers);
	if (data->forks)
		free(data->forks);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->last_meal_mutex);
	while (i < data->num_philosophers)
	{
		// pthread_mutex_destroy(&data->philosophers[i].last_meal_mutex);
		// pthread_mutex_destroy(&data->forks[i]); // --------------- DO i need this one??
		i++;
	}
}
