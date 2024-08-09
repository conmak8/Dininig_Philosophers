/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:41:08 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/09 16:17:30 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}

bool	input_is_valid(int argc, char **argv)
{
	size_t	i;

	if (argc != 5 && argc != 6)
		return (print_error("Incorrect number of arguments\n"), 0);
	++argv;
	while (*argv)
	{
		if (!is_valid_number(*argv))
			return (print_error("Incorrect character in arguments\n"), 0);
		if (ft_atoll(*argv) <= 0)
			return (print_error("Cannot have zero or \
			negative in arguments\n"), 0);
		argv++;
	}
	return (true);
}

void	log_status(t_philosopher *philosopher, char *status)
{
	if (!philosopher->sim_data->stop_simulation)
	{
		pthread_mutex_lock(&philosopher->sim_data->print_mutex);
		printf("%lld %d %s\n", (get_current_time() - \
		philosopher->sim_data->start_time), philosopher->id, status);
		pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
	}
}

int	initialize_data(int argc, char **argv, t_sim_data *data)
{
	int	i;

	i = 0;
	data->num_philosophers = (int)ft_atoll(argv[1]);
	data->death_time = ft_atoll(argv[2]);
	data->eating_time = ft_atoll(argv[3]);
	data->sleeping_time = ft_atoll(argv[4]);
	if (argc == 6)
		data->required_meals = (int)ft_atoll(argv[5]);
	else
		data->required_meals = -1;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("Mutex initialization failed for print_mutex\n");
		return (print_error("Mutex_init Failed at print_mutex\n"), pthread_mutex_destroy(&data->forks[i]), 3); //--------------pthread_mutex_destroy(&data->forks[i]) i don't need thiss
	}
	data->stop_simulation = 0;
	data->start_time = get_current_time();
	
	init_philoshopers(argc, argv, data);
	
	return (1);
}

int	init_philoshopers(int argc, char **argv, t_sim_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!data->philosophers) //it wil not be normed okay
		return (print_error("Malloc Philo Failed\n"), 2);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
	{
		free(data->philosophers);
		pthread_mutex_destroy(&data->print_mutex);
		return (print_error("Malloc Forks Failed\n"), 2);
	}
	while (i < data->num_philosophers)
	{
		init_philo_in(i, data);
		i++;
	}
	return (0);
}

int	init_philo_in(int i, t_sim_data *data)
{
	data->philosophers[i].thread_id = 0;
	data->philosophers[i].id = i + 1;
	data->philosophers[i].meals_count = 0 ;
	data->philosophers[i].time_of_death = get_current_time() + data->death_time;
	data->philosophers[i].sim_data = data;
	data->philosophers[i].left_fork = i;
	data->philosophers[i].right_fork = (i + 1) % data->num_philosophers;
	data->philosophers[i].last_meal_time = data->start_time;
	if (pthread_mutex_init(&data->forks[i], NULL) != 0)
	{
		free(data->philosophers);
		free(data->forks);
		pthread_mutex_destroy(&data->print_mutex);
		printf("Mutex initialization failed for fork %d\n", i);
		return (print_error("Mutex_init Failed at forks\n"), 3);
	}
	return (0);
}
