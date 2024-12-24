#include <philo.h>

static int	is_space(const char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		print_error_and_exit("negative values are forbidden");
	if (!ft_isdigit(*str))
		print_error_and_exit("the input is not a correct digit");
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		print_error_and_exit("use a value < than INT_MAX");
	return (number);
}

// convert a string to long
long	ft_atol(const char *str)
{
	long	number;

	number = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		number = (number * 10) + (*str++ - 48);
	if (number > INT_MAX)
		print_error_and_exit("use a value < than INT_MAX");
	return (number);
}

// Get start simulation time
long	get_time(char c)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		print_error_and_exit("gettimeofday failed");
	if (c == 'S')
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (c == 'M')
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (c == 'm')
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (6969);
}

void	my_usleep(long usec, t_program *program)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time('m');
	while (get_time('m') - start < usec)
	{
		if (ready(program))
			break ;
		elapsed = get_time('m') - start;
		rem = usec - elapsed;

		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time('m') - start < usec)
				;
		}
	}
}
