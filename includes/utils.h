#ifndef UTILS_H
# define UTILS_H

#include "philo.h"

void	error_message(char *text, int signal);
void	check_args(int argc, char **argv);
void	destroy_all(t_engine *engine, char *str, int count, int signal);
size_t	get_current_time(void);
void	print_action(t_philo *philo, char *action);
void	ft_usleep(size_t mls);

#endif   /* UTILS_H */
