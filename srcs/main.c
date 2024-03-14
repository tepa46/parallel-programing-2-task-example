#include "philo.h"
#include "utils.h"
#include "init.h"

int	main(int argc, char **argv)
{
	t_philo		philos[PHILO_MAX_COUNT];
	t_mutex		forks[PHILO_MAX_COUNT];
	t_engine	engine;

	check_args(argc, argv);
	init_engine(&engine, philos, forks);
	init_forks(&engine, forks, ft_atoi(argv[1]));
	init_philos(&engine, philos, forks, argv);

	//control(philos, mutexes, count, th_id);
	//destroy_all(mutexes, philos, count);
	return (0);
}
