#include <philo.h>

void	free_all(t_program *program)
{
	t_philo	*philo;
	int		i;
	int		status;

	i = 0;
	while (i < program->n_philo)
	{
		philo = program->philos + i;
		status = pthread_mutex_destroy(&philo->philo_mutex);
		if (status != 0)
			print_error_and_exit("Cannot destroy mutex");
		++i;
	}
	status = pthread_mutex_destroy(&program->write_mutex);
	if (status != 0)
		print_error_and_exit("Cannot destroy mutex");
	status = pthread_mutex_destroy(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("Cannot destroy mutex");
	free(program->forks);
	free(program->philos);
}
