#include <philo.h>

void	write_status(int status, t_philo *philo)
{
	long	elapsed;
	int		s;

	elapsed = get_time('M') - philo->program->start_simulation;
	if (philo->full)
		return ;
	s = pthread_mutex_lock(&philo->program->write_mutex);
	if (s != 0)
		print_error_and_exit("cannot lock mutex");
	if (!ready(philo->program))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d is died\n", elapsed, philo->id);
	}
	s = pthread_mutex_unlock(&philo->program->write_mutex);
	if (s != 0)
		print_error_and_exit("cannot unlock mutex");
}
