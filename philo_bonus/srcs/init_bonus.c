/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:37:23 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/16 18:37:25 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	init_philos(t_engine *en, t_philo *philos, char **argv, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		philos[i].id = i + 1;
		philos[i].times.die = ft_atoi(argv[2]);
		philos[i].times.eat = ft_atoi(argv[3]);
		philos[i].times.sleep = ft_atoi(argv[4]);
		philos[i].times.last_meal = get_current_time();
		philos[i].times.born_time = get_current_time();
		philos[i].must_eat = -1;
		if (argv[5])
			philos[i].must_eat = ft_atoi(argv[5]);
		philos[i].meals_eaten = 0;
		philos[i].philo_count = count;
		philos->sems.fork_sem = en->fork_sem;
		philos->sems.meal_sem = en->meal_sem;
		philos->sems.write_sem = en->write_sem;
	}
}

void	init_engine(t_engine *en, t_philo *philos, pid_t *proc_ids, int count)
{
	int	i;

	i = -1;
	en->philos = philos;
	en->philo_count = count;
	en->proc_ids = proc_ids;
	while (++i < count)
		proc_ids[i] = -1;
	en->fork_sem = sem_open(FORK_SEM_NAME, O_CREAT | O_EXCL, 0644, count);
	en->meal_sem = sem_open(MEAL_SEM_NAME, O_CREAT | O_EXCL, 0644, 0);
	en->write_sem = sem_open(WRITE_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (en->fork_sem == SEM_FAILED || en->meal_sem == SEM_FAILED
		|| en->write_sem == SEM_FAILED)
		destroy_all(en, "[Semaphore Open ERROR]\n", true, 1);
	if (sem_unlink(FORK_SEM_NAME) == -1 || sem_unlink(MEAL_SEM_NAME) == -1
		|| sem_unlink(WRITE_SEM_NAME) == -1)
		destroy_all(en, "[Semaphore Unlink ERROR]\n", true, 1);
}
