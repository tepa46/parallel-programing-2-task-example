#include "philo.h"
#include "utils.h"
#include "init.h"
#include "simulation.h"

int	main(int argc, char **argv)
{
	t_philo		philos[PHILO_MAX_COUNT];
	t_mutex		forks[PHILO_MAX_COUNT];
	t_engine	engine;

	check_args(argc, argv);
	init_engine(&engine, philos, forks);
	init_forks(&engine, forks, ft_atoi(argv[1]));
	init_philos(&engine, philos, forks, argv);
	start_simulation(&engine, philos[0].philo_count);
	destroy_all(&engine, NULL, philos[0].philo_count, 0);
	return (0);
}
