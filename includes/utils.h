#ifndef UTILS_H
# define UTILS_H

#include "philo.h"

void	error_message(char *text, int signal);
void	check_args(int argc, char **argv);
void	destroy_mutexes(t_engine *engine, char *str, int count, int signal);

#endif   /* UTILS_H */
