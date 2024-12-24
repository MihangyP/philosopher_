#include <philo.h>

void	update_last_meal_time(t_philo *philo)
{
	int	status;

	status = pthread_mutex_lock(&philo->philo_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	philo->last_meal_time = get_time('M');
	status = pthread_mutex_unlock(&philo->philo_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
}

void	update_philo_full(t_philo *philo)
{
	int	status;

	status = pthread_mutex_lock(&philo->philo_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	philo->full = true;
	status = pthread_mutex_unlock(&philo->philo_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");

}

void	eat(t_philo *philo)
{
	int	status;

	status = pthread_mutex_lock(&philo->first_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	write_status(TAKE_FIRST_FORK, philo);
	status = pthread_mutex_lock(&philo->second_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	write_status(TAKE_SECOND_FORK, philo);
	update_last_meal_time(philo);
	philo->meals_counter += 1;
	write_status(EATING, philo);
	my_usleep(philo->program->t_eat, philo->program);
	if (philo->program->n_meals > 0 && philo->meals_counter == philo->program->n_meals)
		update_philo_full(philo);
	status = pthread_mutex_unlock(&philo->first_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	status = pthread_mutex_unlock(&philo->second_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
}
