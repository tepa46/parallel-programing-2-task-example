#ifndef INIT_H
# define INIT_H

# include "philo.h"

void	init_philos(t_engine *en, t_philo *philos, t_mutex *forks, char **argv);
void	init_forks(t_engine* engine, t_mutex *forks, int count);
void	init_engine(t_engine *engine, t_philo *philos, t_mutex *forks);
size_t	get_current_time(void);
void	print_action(t_philo *philo, char *action);
void	ft_usleep(size_t mls);

#endif   /* INIT_H */
