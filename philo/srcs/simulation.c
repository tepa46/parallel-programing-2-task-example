/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:59:38 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/15 17:03:37 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "pthread.h"
#include "errno.h"

void	philo_routine(t_philo *philo)
{
    if (pthread_mutex_trylock(philo->mutexes.left_fork) == EBUSY) {
        ft_usleep(1);
        return;
    }
    else {
        if (pthread_mutex_trylock(philo->mutexes.right_fork) == EBUSY) {
            pthread_mutex_unlock(philo->mutexes.left_fork);
            ft_usleep(1);
            return;
        }
    }
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

void	*start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->times.born_time = get_current_time();
	philo->times.last_meal = get_current_time();
	pthread_mutex_unlock(philo->mutexes.meal_lock);
    while (true) {
        pthread_mutex_lock(philo->mutexes.meal_lock);
        if (*(philo->finish) || philo->meals_eaten >= philo->must_eat) {
            pthread_mutex_unlock(philo->mutexes.meal_lock);
            break;
        }

        if (get_current_time() - philo->times.last_meal > philo->times.die) {
            print_action(philo, RED " died" RESET);
            *(philo->finish) = true;
            pthread_mutex_unlock(philo->mutexes.meal_lock);
            break;
        }
        pthread_mutex_unlock(philo->mutexes.meal_lock);
        philo_routine(philo);
    }
	return (NULL);
}

void	launcher(t_engine *engine, int count)
{
    int		i;

    i = -1;
    while (++i < count)
    {
        if (pthread_create(&engine->philos[i].thread_id, NULL,
                           start_simulation, &engine->philos[i]) != 0)
            destroy_all(engine, "[Thread Creation ERROR]\n", count, 1);
    }
    i = -1;
    while (++i < count)
    {
        if (pthread_join(engine->philos[i].thread_id, NULL) != 0)
            destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
    }
}
