#include "philo.h"

#include "philo.h"

static void	single_philosopher_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->print_mutex);
	philosopher->last_meal_time = get_current_time() + philosopher->sim_data->death_time;
	pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
	pthread_mutex_unlock(&philosopher->sim_data->forks[philosopher->right_fork]);
}

static void	philosopher_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->left_fork]);
	log_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->sim_data->forks[philosopher->right_fork]);
	log_status(philosopher, "has taken a fork");
	// pthread_mutex_lock(&philosopher->sim_data->print_mutex);
	philosopher->last_meal_time = get_current_time() + philosopher->sim_data->death_time;
	// pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
	log_status(philosopher, "is eating");
	usleep(philosopher->sim_data->eating_time * 1000);  // grapse mia diki sou akriveia!!!---------------------
	pthread_mutex_unlock(&philosopher->sim_data->forks[philosopher->right_fork]);
	pthread_mutex_unlock(&philosopher->sim_data->forks[philosopher->left_fork]);
	if (philosopher->sim_data->required_meals > 0) // pou ta auxanw...????  kai pote stamataw ??
	{
		pthread_mutex_lock(&philosopher->sim_data->print_mutex);
		philosopher->meals_count++;
		pthread_mutex_unlock(&philosopher->sim_data->print_mutex);
	}
}


void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->sim_data->num_philosophers == 1)
		return (single_philosopher_routine(philosopher), NULL);
	if (philosopher->id % 2 != 0)
	{
		log_status(philosopher, "is thinking");
		usleep(philosopher->sim_data->eating_time * 500);
	}
	
	while (!philosopher->sim_data->stop_simulation) //if i dd supervisor this will be data race.
	{
		philosopher_eat(philosopher);
		// if (philosopher->sim_data->stop_simulation)
		// 	break ;
		log_status(philosopher, "is sleeping");
		usleep(philosopher->sim_data->sleeping_time * 1000);
		// if (philosopher->sim_data->stop_simulation)
		// 	break ;
		log_status(philosopher, "is thinking");
	}
	return (NULL);
}

/* 
#include "philo.h"

void philo_eat(t_philo *philo) {
    pthread_mutex_lock(&philo->left_fork);
    pthread_mutex_lock(&philo->right_fork);

    // Update philosopher's state to eating
    philo->state = EATING;
    printf("%lld %d is eating\n", current_time() - philo->data->start_time, philo->id);

    // Simulate eating
    usleep(philo->data->time_to_eat * 1000);

    // Release forks after eating
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(&philo->left_fork);
}

void philo_sleep(t_philo *philo) {
    // Update philosopher's state to sleeping
    philo->state = SLEEPING;
    printf("%lld %d is sleeping\n", current_time() - philo->data->start_time, philo->id);

    // Simulate sleeping
    usleep(philo->data->time_to_sleep * 1000);
}

void philo_think(t_philo *philo) {
    // Update philosopher's state to thinking
    philo->state = THINKING;
    printf("%lld %d is thinking\n", current_time() - philo->data->start_time, philo->id);

    // Simulate thinking
    usleep(1000); // Small delay to prevent busy waiting
} */
