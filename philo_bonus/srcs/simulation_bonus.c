/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:37:57 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/16 18:37:59 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	*die_checker(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (true)
	{
		if (get_current_time() - philo->times.last_meal > philo->times.die)
		{
			print_action(philo, RED"died"RESET);
			sem_wait(philo->sems.write_sem);
			sem_close(philo->sems.fork_sem);
			sem_close(philo->sems.meal_sem);
			sem_close(philo->sems.write_sem);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

void	*meal_checker(void *ptr)
{
	t_engine	*engine;
	int			finished;

	finished = 0;
	engine = (t_engine *)ptr;
	while (true)
	{
		sem_wait(engine->meal_sem);
		++finished;
		//printf("AAAAAAAAAA %d", finished);
		if (finished == engine->philos[0].must_eat)
		{
			//sem_wait(engine->write_sem);
			destroy_all(engine, NULL, true, 0);
		}
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	sem_wait(philo->sems.fork_sem);
	print_action(philo, "has taken a fork");
	sem_wait(philo->sems.fork_sem);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	philo->times.last_meal = get_current_time();
	philo->meals_eaten += 1;
	if (philo->meals_eaten == philo->must_eat)
	{
		sem_post(philo->sems.meal_sem);
	}
	ft_usleep(philo->times.eat);
	sem_post(philo->sems.fork_sem);
	sem_post(philo->sems.fork_sem);
	print_action(philo, "is sleeping");
	ft_usleep(philo->times.sleep);
	print_action(philo, "is thinking");
}

void	start_simulation(t_philo *philo)
{
	t_id	die_checker_id;

	if (pthread_create(&die_checker_id, NULL, die_checker, philo) != 0
		|| pthread_detach(die_checker_id) != 0)
	{
		sem_close(philo->sems.fork_sem);
		sem_close(philo->sems.meal_sem);
		sem_close(philo->sems.write_sem);
		error_message("[Thread Error]\n", 1);
	}
	// philo->sems.meal_sem = sem_open(MEAL_SEM_NAME, 0);
	// philo->sems.fork_sem = sem_open(FORK_SEM_NAME, 0);
	// philo->sems.write_sem = sem_open(WRITE_SEM_NAME, 0);
	philo->times.born_time = get_current_time();
	philo->times.last_meal = get_current_time();
	while (true)
		philo_routine(philo);
}

void	launcher(t_engine *engine, int count)
{
	t_id	meal_checker_id;
	t_philo	*philos;
	pid_t	id;
	int		i;

	i = -1;
	philos = engine->philos;
	if (philos[0].must_eat > 0)
	{
		if (pthread_create(&meal_checker_id, NULL, meal_checker, engine) != 0)
			destroy_all(engine, "[Thread Open ERROR]\n", true, 1);
		if (pthread_detach(meal_checker_id) != 0)
			destroy_all(engine, "[Thread Detach ERROR]\n", true, 1);
	}
	while (++i < count)
	{
		id = fork();
		engine->proc_ids[i] = id;
		if (id == -1)
			destroy_all(engine, "[Fork ERROR]\n", true, 1);
		if (id == 0)
			start_simulation(&philos[i]);
	}
	waitpid(-1, NULL, 0);
}
