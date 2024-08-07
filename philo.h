/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:31:17 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 17:59:41 by cmakario         ###   ########.fr       */
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

typedef struct s_sim_data
{
	int				num_philosophers;
	long long				death_time;
	long long				eating_time;
	long long				sleeping_time;
	int				required_meals;
	
	// int				stop_simulation;
	// long long		start_time;
	// pthread_mutex_t	*forks;
	// pthread_mutex_t	print_mutex;
	// t_philosopher	*philosophers;
}					t_sim_data;

typedef struct s_philosopher
{
	pthread_t		thread_id;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_count;
	long long		last_meal_time;
	struct s_sim_data	*sim_data;
}					t_philosopher;

// typedef struct s_philo
// {
// 	pthread_t		thread;
// 	int				id;
// 	long long		t_of_death;
// 	long			times_ate;
// 	bool			is_done;
// 	t_data			*data;
// 	pthread_mutex_t	r_fork;
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	lock_eating;
// }	t_philo;



// typedef struct s_data
// {
// 	int				num_philos;
// 	long long		t_die;
// 	long long		t_eat;
// 	long long		t_sleep;
// 	long			notepme;
	
// 	t_philo			*philo;
// 	long long		start_time;
// 	bool			any_dead;
// 	int				philos_done;
// 	pthread_mutex_t	lock_dead;
// 	pthread_mutex_t	lock_done;
// 	pthread_mutex_t	lock_print;
// }	t_data;


/* -------------------------- utils.c ------------------------- */

size_t	ft_strlen(const char *s);
int		print_error(char *msg);
int		is_valid_number(char *str);
bool	input_is_valid(int argc, char **argv);
int		ft_atoll(const char *str);
int		ft_isdigit(int a);
int		initilize_data(int argc,char **argv,t_sim_data *data);


#endif // PHILO_H