#include <philo.h>

bool	running(pthread_mutex_t *mutex, long *threads, long n_philo)
{
	bool	return_value;
	int		status;

	return_value = false;
	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	if (n_philo == *threads)
		return_value = true;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (return_value);
}

bool	get_philo_full(pthread_mutex_t *mutex, bool *value)
{
	int		status;
	bool	return_value;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	return_value = *value;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (return_value);
}

long	get_last_meal_time(pthread_mutex_t *mutex, long *value)
{
	long	return_value;
	int		status;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	return_value = *value;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (return_value);
}

// convert t_die to millisecond
bool	died(t_philo *philo)
{
	long	elapsed;
	long	t_die;

	if (get_philo_full(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time('M') - get_last_meal_time(&philo->philo_mutex, &philo->last_meal_time);
	t_die = philo->program->t_die / 1000;
	if (elapsed > t_die)
		return (true);
	return (false);
}

void	*monitoring(void *data)
{
	t_program	*program;
	int			i;
	int			status;

	program = (t_program *)data;
	while (!running(&program->program_mutex, &program->threads_running_nbr, program->n_philo))
		;
	while (!ready(program))
	{
		i = 0;
		while (i < program->n_philo && !ready(program))
		{
			if (died(program->philos + i))
			{
				status = pthread_mutex_lock(&program->program_mutex);
				if (status != 0)
					print_error_and_exit("cannot lock mutex");
				program->end_simulation = true;
				status = pthread_mutex_unlock(&program->program_mutex);
				if (status != 0)
					print_error_and_exit("cannot unlock mutex");
				write_status(DIED, program->philos + i);
			}
			++i;
		}
	}
	return (NULL);
}
