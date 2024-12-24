#include <philo.h>

void	think(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	t_eat = philo->program->t_eat;
	t_sleep = philo->program->t_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (!pre_simulation)
		write_status(THINKING, philo);
	write_status(THINKING, philo);
	if (philo->program->n_philo % 2 == 0)
		return ;
	if (t_think < 0)
		t_think = 0;
	my_usleep(t_think * 0.42, philo->program);
}
