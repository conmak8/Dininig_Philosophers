/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:31:17 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/13 22:40:21 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philosopher t_philosopher ;

typedef struct s_sim_data
{
	int				num_philosophers;
	long long		death_time;
	long long		eating_time;
	long long		sleeping_time;
	int				required_meals;

	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t stop_mutex;
	// pthread_mutex_t last_meal_mutex;
	int				stop_simulation;
	long long		start_time;
}					t_sim_data;

typedef struct s_philosopher
{
	pthread_t		thread_id;
	int				id;
	bool			is_eating;
	int				meals_count;
	int				left_fork;
	int				right_fork;
	
	struct s_sim_data	*sim_data;
	long long		last_meal_time;
	pthread_mutex_t last_meal_mutex;
}	t_philosopher;

/* -------------------------- utils.c ------------------------- */

size_t		ft_strlen(const char *s);
int			print_error(char *msg);
int			is_valid_number(char *str);
bool		input_is_valid(int argc, char **argv);
long long	ft_atoll(const char *str);
int			ft_isdigit(int a);
int			initialize_data(int argc,char **argv,t_sim_data *data);


void	*philosopher_routine(void *arg);
void	log_status(t_philosopher *philosopher, char *status);

int	launch_threads(t_sim_data *data, t_philosopher *philosophers);
long long	get_current_time(void);
void	*monitor_philosophers(void *arg);

int	init_philoshopers(t_sim_data *data);

int	init_philo_in(int i, t_sim_data *data);
void	ft_msleep(long long msec);

void	ft_cleanup(t_sim_data *data);
int		stop_simulation(t_sim_data *data);


#endif // PHILO_H