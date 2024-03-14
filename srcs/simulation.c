#include <sys/time.h>
#include "simulation.h"
#include "utils.h"


#include <stdio.h>

bool	isAllEat(t_philo *philos)
{
	int		finished;
	int		i;

	i = -1;
	finished = 0;
	if (philos[0].must_eat == -1)
		return (false);
	while (++i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eat)
			++finished;
		pthread_mutex_unlock(philos->mutexes.meal_lock);
	}
	if (finished == philos[0].must_eat)
		return (true);
	return (false);
}

bool	checkPhiloDie(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.meal_lock);
		if (get_current_time() - philos[i].times.last_meal > philos[i].times.die)
		{
			pthread_mutex_unlock(philos->mutexes.meal_lock);
			print_action(&philos[i], RED" died"RESET);
			pthread_mutex_lock(philos->mutexes.dead_lock);
			*(philos[i].isAnyPhiloDead) = true;
			pthread_mutex_unlock(philos->mutexes.dead_lock);
			return (true);
		}
		pthread_mutex_unlock(philos->mutexes.meal_lock);
	}
	return (false);
}

void	*obsorver(void *ptr)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = (t_philo *)ptr;
	while(!checkPhiloDie(philos) && !isAllEat(philos))
		;
	return (NULL);
}

bool	isAnyPhiloDead(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes.dead_lock);
	if (*(philo->isAnyPhiloDead))
	{
		pthread_mutex_unlock(philo->mutexes.dead_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->mutexes.dead_lock);
	return (false);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!isAnyPhiloDead(philo))
	{
		pthread_mutex_lock(philo->mutexes.left_fork);
		print_action(philo, " has taken a fork");
		pthread_mutex_lock(philo->mutexes.right_fork);
		print_action(philo, " has taken a fork");
		pthread_mutex_lock(philo->mutexes.meal_lock);
		print_action(philo, " is eating");
		philo->times.last_meal = get_current_time();
		philo->meals_eaten += 1;
		pthread_mutex_unlock(philo->mutexes.meal_lock);
		ft_usleep(philo->times.eat);
		pthread_mutex_unlock(philo->mutexes.left_fork);
		pthread_mutex_unlock(philo->mutexes.right_fork);
		print_action(philo, " is sleeping");
		ft_usleep(philo->times.sleep);
		print_action(philo, " is thinking");
	}
	return (NULL);
}

void	start_simulation(t_engine *engine, int count)
{
	t_id	obsorver_id;
	int		i;

	if (pthread_create(&obsorver_id, NULL, &obsorver, engine->philos) != 0)
		destroy_all(engine, "[Thread Creation ERROR]\n", count, 1);
	i = -1;
	while (++i < count)
	{
		if (pthread_create(&engine->philos[i].thread_id, NULL, philo_routine, 
			&engine->philos[i]) != 0)
			destroy_all(engine, "[Thread Creation ERROR]\n", count, 1);
	}
	if (pthread_join(obsorver_id, NULL) != 0)
		destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	i = -1;
	while (++i < count)
	{
		if (pthread_join(engine->philos[i].thread_id, NULL) != 0)
			destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	}
}
