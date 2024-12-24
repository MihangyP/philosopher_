#include <philo.h>

// Init philosopher structure
void	init_all_philosophers(t_program *program)
{
	t_philo	*philo;
	int		i;
	int		status;

	i = 0;
	while (i < program->n_philo)
	{
		philo = program->philos + i;
		philo->full = false;
		philo->meals_counter = 0;
		philo->id = i + 1;
		philo->program = program;
		status = pthread_mutex_init(&philo->philo_mutex, NULL);
		if (status != 0)
			print_error_and_exit("cannot init mutex");
		philo->first_fork = &program->forks[(i + 1) % program->n_philo];
		philo->second_fork = &program->forks[i];
		if (!(philo->id % 2))
		{
			philo->first_fork = &program->forks[i];
			philo->second_fork = &program->forks[(i + 1) % program->n_philo];
		}
		++i;
	}
}

// Init forks
void	init_forks(t_program *program)
{
	int	i;
	int	status;

	i = -1;
	while (++i < program->n_philo)
	{
		program->forks[i].id = i;
		status = pthread_mutex_init(&program->forks[i].fork, NULL);
		if (status != 0)
			print_error_and_exit("cannot init mutex");
	}
}

// Init data, mutexes, and the stuffs we need
void	init_data(t_program *program)
{
	int	status;

	program->end_simulation = false;
	program->all_threads_ready = false;
	program->threads_running_nbr = 0;
	program->philos = malloc(program->n_philo * sizeof(t_philo));
	if (!program->philos)
		print_error_and_exit("Malloc error");
	status = pthread_mutex_init(&program->program_mutex, NULL);
	if (status != 0)
		print_error_and_exit("cannot init mutex");
	status = pthread_mutex_init(&program->write_mutex, NULL);
	if (status != 0)
		print_error_and_exit("cannot init mutex");
	program->forks = malloc(program->n_philo * sizeof(t_fork));
	if (!program->forks)
		print_error_and_exit("Malloc error");
	init_forks(program);
	init_all_philosophers(program);
}
