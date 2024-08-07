/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:41:08 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 19:32:17 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_isdigit(int a)
{
	if (a > 47 && a < 58)
		return (1);
	return (0);
}
int	ft_atoll(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++ ;
	return (i);
}

int	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return(EXIT_FAILURE);
}

bool	input_is_valid(int argc, char **argv)
{
	size_t i;
	// handle args number validity
	if (argc != 5 && argc != 6)
		return(print_error("Incorrect number of arguments\n"));
	// handle args type validity
	while (*argv)
	{
		i = 0;
		
		if (!is_valid_number(argv[i]))
			return(print_error("Incorrect character in arguments\n"));
		i++;
		if (ft_atoll(*argv) <= 0)
			return(print_error("Cannot have zero or negative in arguments\n"));
		argv++;
	}
	return(true);
}

int	initilize_data(int argc,char **argv,t_sim_data *data)
{
	int i;

	i = 0;
	
	// general given data
	data->num_philosophers =(int)ft_atoll(argv[1]);
	data->death_time = ft_atoll(argv[2]);
	data->eating_time = ft_atoll(argv[3]);
	data->sleeping_time = ft_atoll(argv[4]);
	if (argc == 6)
		data->required_meals = (int)ft_atoll(argv[5]);
	else
		data->required_meals = -1;
		
	if (!pthread_mutex_init(&data->print_mutex, NULL))
			return (print_error("Mutex_init Failed\n"), pthread_mutex_destroy(&data->forks[i]), 3);
	
	data->stop_simulation = 0;
	
	//creation of this struct for philos
	
	if (!(data->philosophers = malloc(size_of(t_philosopher) * data->num_philosophers)))
	{
		free(data->philosophers);
		return (print_error("Malloc Philo Failed\n"), 2);
	}
	
	if (!(data->forks = malloc(sizeof(pthread_mutex_t) * sim_data->num_philosophers)))
	{
		free(data->forks);
		return (print_error("Malloc Forks Failed\n"), 2);
	}

	while (i < data->num_philosophers)
	{
		data->philosophers[i].thread_id = 0;
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_count = 0 ;
		data->philosophers[i].time_of_death = get_current_time() + data->death_time;
		data->philosophers[i].sim_data = data;

		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->num_philosophers;
		
		if (!pthread_mutex_init(&data->forks[i], NULL))
			return (print_error("Mutex_init Failed\n"),pthread_mutex_destroy(&data->print_mutex), 3);
	}
	return(1)
}

