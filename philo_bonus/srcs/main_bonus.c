/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:37:37 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/16 18:37:40 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "utils_bonus.h"
#include "init_bonus.h"
#include "simulation_bonus.h"

void	check_args(int argc, char **argv)
{
	int		i;
	long	num;

	i = 0;
	if (argc < 5 || argc > 6)
		error_message("[Argument Count ERROR]\n", 1);
	while (++i < argc)
	{
		num = ft_atoi(argv[i]);
		if (i == 1 && (num < 1 || num > PHILO_MAX_COUNT))
			error_message("[Argument ERROR]\n", 1);
		else if (i == 5 && (num < 0 || num > INT_MAX))
			error_message("[Argument ERROR]\n", 1);
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			error_message("[Argument ERROR]\n", 1);
	}
}

int	main(int argc, char **argv)
{
	t_philo		philos[PHILO_MAX_COUNT];
	pid_t		proc_ids[PHILO_MAX_COUNT];
	t_engine	engine;

	check_args(argc, argv);
	init_engine(&engine, philos, proc_ids, ft_atoi(argv[1]));
	init_philos(&engine, philos, argv, engine.philo_count);
	launcher(&engine, engine.philo_count);
	destroy_all(&engine, NULL, true, 0);
	return (0);
}
