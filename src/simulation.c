#include <philo.h>

void	desynchronise_philos(t_philo *philo)
{
	if (philo->program->n_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(30000, philo->program);		
	}
	else
	{
		if (philo->id % 2)	
			think(philo, true);
	}
}

static void	finish_simulation(t_program *program)
{
	int	status;

	status = pthread_mutex_lock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("connat lock mutex");
	program->end_simulation = true;
	status = pthread_mutex_unlock(&program->program_mutex);
		print_error_and_exit("connat unlock mutex");
	status = pthread_join(program->monitor, NULL);
	if (status != 0)
		print_error_and_exit("connat join thread");
}

static void	simulation_next(t_program *program)
{
	int	status;
	int	i;

	status = pthread_mutex_lock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("connat lock mutex");
	program->all_threads_ready = true;
	status = pthread_mutex_unlock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("connat unlock mutex");
	i = -1;
	while (++i < program->n_philo)
	{
		status = pthread_join(program->philos[i].thread, NULL);
		if (status != 0)
			print_error_and_exit("connat join thread");
	}
	finish_simulation(program);
}

bool	dinner_finished(t_program *program)
{
	bool	return_value;
	int		status;

	status = pthread_mutex_lock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	return_value = program->end_simulation;
	status = pthread_mutex_unlock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (return_value);
}

// check if all threads is ready
bool	ready(t_program *program)
{
	int	status;
	int	return_value;

	status = pthread_mutex_lock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	return_value = program->all_threads_ready;
	status = pthread_mutex_unlock(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (return_value);
}

void	value_changement(t_philo *philo)
{
	int	status;

	status = pthread_mutex_lock(&philo->philo_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	philo->last_meal_time = get_time('M');
	status = pthread_mutex_unlock(&philo->philo_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	status = pthread_mutex_lock(&philo->program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	philo->program->threads_running_nbr += 1;
	status = pthread_mutex_unlock(&philo->program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
}

void	my_sleep(t_philo *philo)
{
	write_status(SLEEPING, philo);
	my_usleep(philo->program->t_sleep, philo->program);
}

void	*deep_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!ready(philo->program))
		;
	value_changement(philo);
	desynchronise_philos(philo);
	while (!dinner_finished(philo->program))
	{
		if (philo->full)
			break ;
		eat(philo);
		my_sleep(philo);
		think(philo, false);
	}
	return (NULL);
}

// Start the philosopher's dinner simulation
void	simulation(t_program *program)
{
	int	i;
	int	status;

	if (!program->n_meals)
		return ;
	else if (1 == program->n_philo)
	{
		status = pthread_create(&program->philos[0].thread, NULL, one_philo_simulation, &program->philos[0]);
		if (status != 0)
			print_error_and_exit("cannot create thread");
	}
	else
	{
		i = -1;
		while (++i < program->n_philo)
		{
			status = pthread_create(&program->philos[i].thread, NULL, deep_simulation, &program->philos[i]);
			if (status != 0)
				print_error_and_exit("cannot create thread");
		}
	}
	status = pthread_create(&program->monitor, NULL, monitoring, program);
	if (status != 0)
		print_error_and_exit("cannot create thread");
	program->start_simulation = get_time('M');
	simulation_next(program);
}
