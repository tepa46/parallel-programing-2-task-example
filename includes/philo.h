#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include "libft.h"

typedef pthread_t		t_id;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

# define PHILO_MAX_COUNT 300

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write_lock;
	t_mutex	*meal_lock;
	t_mutex	*dead_lock;
}	t_mutexes;

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	last_eat;
	size_t	born_time;
}	t_times;

typedef struct s_philo
{
	int			id;
	t_times		times;
	t_mutexes	mutexes;
	int			must_eat;
	int			meals_eaten;
	int			philo_count;
}	t_philo;

typedef struct s_engine
{
	t_mutex	write_lock;
	t_mutex	meal_lock;
	t_mutex	dead_lock;
	t_philo	*philos;
	t_mutex	*forks;
}	t_engine;

#endif   /* PHILO_H */
