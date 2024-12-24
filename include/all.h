#ifndef PHILO_H
# define PHILO_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define DEBUG_MODE 0

typedef enum	e_opcode
{
	LOCK = 0,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

typedef enum	e_philo_status
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_philo_status;

typedef struct	s_table	t_table;

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct	s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;

struct	s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			all_threads_ready;
	long			threads_running_nbr;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;	
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

#endif
