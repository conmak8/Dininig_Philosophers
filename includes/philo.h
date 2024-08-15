/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:31:17 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/15 14:54:24 by cmakario         ###   ########.fr       */
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

typedef struct s_philosopher	t_philosopher ;
typedef struct s_sim_data
{
	int					num_philosophers;
	long long			death_time;
	long long			eating_time;
	long long			sleeping_time;
	int					required_meals;

	t_philosopher		*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		last_meal_mutex;

	pthread_mutex_t		start_mutex;
	int					ready_threads;

	int					stop_simulation;
	long long			start_time;
}						t_sim_data;

typedef struct s_philosopher
{
	pthread_t			thread_id;
	int					id;
	int					meals_count;
	int					left_fork;
	int					right_fork;
	int					finished;

	long long			last_meal_time;
	struct s_sim_data	*sim_data;
}						t_philosopher;

/* -------------------------- philo_actions ------------------------- */

/* ------- routinses.c -------- */
void		single_philosopher_routine(t_philosopher *philosopher);
void		philosopher_eat(t_philosopher *philosopher);
int			stop_simulation(t_sim_data *data);
void		*philosopher_routine(void *arg);
void		routine_loop_in(t_philosopher *philosopher);

/* ------- supervisor.c -------- */
bool		monitor_meals_in_1(t_sim_data *data, int i, \
								int *philos_finished_meals);
void		mon_lock_meal_2(t_sim_data *data, int i, long long	*last_meal);
void		mon_lock_meal_3(t_sim_data *data, int i);
void		*monitor_philosophers(void *arg);

/* -------------------------- philo_initialize ------------------------- */

/* ------- args_validation.c -------- */
bool		input_is_valid(int argc, char **argv);

/* ------- initialize.c -------- */
int			initialize_data(int argc, char **argv, t_sim_data *data);
int			init_philoshopers(t_sim_data *data);
int			init_philo_in(int i, t_sim_data *data);

/* ------- threads.c -------- */
int			launch_threads(t_sim_data *data, t_philosopher *philosophers);

/* -------------------------- philo_utils ------------------------- */

/* ------- utils1.c -------- */
long long	get_current_time(void);
int			ft_isdigit(int a);
long long	ft_atoll(const char *str);
int			is_valid_number(char *str);
size_t		ft_strlen(const char *s);

/* ------- utils2.c -------- */
int			print_error(char *msg);
void		log_status(t_philosopher *philosopher, char *status);
void		ft_msleep(long long msec);
void		ft_cleanup(t_sim_data *data);

#endif // PHILO_H
