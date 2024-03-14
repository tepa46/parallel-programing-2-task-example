#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "utils.h"

void	error_message(char *text, int signal)
{
	if (text)
		write (2, text, ft_strlen(text) + 1);
	exit(signal);
}

void	check_args(int argc, char **argv)
{
	int		i;
	long	num;

	i = 0;
	if (argc < 5 || argc > 6)
		error_message("[Argument Count ERROR]\n", 1);
	while (++i < argc)
	{
		num = ft_atoi(argv[i]);
		if (i == 1 && (num < 1 || num > PHILO_MAX_COUNT))
			error_message("[Argument ERROR]\n", 1);
		else if (i == 5 && (num < 0 || num > INT_MAX))
			error_message("[Argument ERROR]\n", 1);
		else if (num < 1 || num > INT_MAX)
			error_message("[Argument ERROR]\n", 1);
	}
}

void	destroy_mutexes(t_engine *engine, char *str, int count, int signal)
{
	while (--count >= 0)
		pthread_mutex_destroy(&engine->forks[count]);
	pthread_mutex_destroy(&engine->write_lock);
	pthread_mutex_destroy(&engine->meal_lock);
	pthread_mutex_destroy(&engine->dead_lock);
	error_message(str, signal);
}