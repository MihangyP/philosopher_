#include <philo.h>

// Extract all arguments and put them into program
// We need to convert timestamp to microsecond
void	extract_data(t_program *program, char **av)
{
	program->n_philo = ft_atol(av[1]);
	program->t_die = ft_atol(av[2]) * 1000;
	program->t_eat = ft_atol(av[3]) * 1000;
	program->t_sleep = ft_atol(av[4]) * 1000;
	program->n_meals = -69;
	if (program->t_die < 60 * 1000 || 
		program->t_eat < 60 * 1000 ||
		program->t_sleep < 60 * 1000)
		print_error_and_exit("Timestamp should major than 60ms");
	if (av[5])
		program->n_meals = ft_atol(av[5]);
}

// Run the program
void	run_program(t_program *program, char **av)
{
	extract_data(program, av);
	init_data(program);
	simulation(program);
}

int	main(int ac, char **av)
{
	t_program	program;

	if (ac == 5 || ac == 6)
		run_program(&program, av);
	else
		print_error_and_exit("Usage example: ./philo 5 800 200 200 [5]");
	free_all(&program);
	return (0);
}
