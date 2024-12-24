#include <philo.h>

void	*one_philo_simulation(void *data)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)data;
	while (!ready(philo->program))
		;
	update_last_meal_time(philo);
	status = pthread_mutex_lock(&philo->program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	philo->program->threads_running_nbr += 1;
	status = pthread_mutex_unlock(&philo->program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	write_status(TAKE_FIRST_FORK, philo);
	while (!ready(philo->program))
		usleep(200);
	return (NULL);
}
