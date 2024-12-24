#ifndef PHILO_H
# define PHILO_H

# include <libft.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

// philosopher status enum
enum e_status
{
	EATING = 1,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
};

// to access to all_data with t_program
typedef struct s_program	t_program;

// fork structure
typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

// a single philo structure
typedef struct	s_philo
{
	int				id;
	long			meals_counter;
	long			last_meal_time;
	bool			full;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread;
	t_program		*program;
	t_fork			*first_fork;
	t_fork			*second_fork;
}	t_philo;

// all data
struct	s_program
{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_meals;
	long			start_simulation;
	long			threads_running_nbr;
	bool			end_simulation;
	bool			all_threads_ready;
	pthread_t		monitor;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	program_mutex;	
	pthread_mutex_t	write_mutex;
};

/* Prototypes */
// Error
void	print_error_and_exit(char *error_message);
// Free
void	free_all(t_program *program);
// Utils
long	ft_atol(const char *str);
long	get_time(char c);
void	my_usleep(long usec, t_program *program);
// Init
void	init_data(t_program *program);
// Simulation
void	simulation(t_program *program);
bool	ready(t_program *program);
// One Philosopher Simulation
void	*one_philo_simulation(void *data);
void	update_last_meal_time(t_philo *philo);
// Eat
void	eat(t_philo *philo);
// Think
void	think(t_philo *philo, bool pre_simulation);
// Monitoring
void	*monitoring(void *data);
// Write Status
void	write_status(int status, t_philo *philo);

#endif // PHILO_H
