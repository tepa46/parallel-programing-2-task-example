#ifndef SIMULATION_H
# define SIMULATION_H

#include <stdbool.h>
# include "philo.h"

bool	isAllEat(t_philo *philos);
void	*obsorver(void *ptr);
void	*philo_routine(void *ptr);
void	start_simulation(t_engine *engine, int count);

#endif   /* SIMULATION_H */
