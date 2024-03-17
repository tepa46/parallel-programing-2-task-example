/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:39:33 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/16 18:40:19 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_BONUS_H
# define INIT_BONUS_H

# include "philo_bonus.h"

void	init_philos(t_engine *en, t_philo *philos, char **argv, int count);
void	init_engine(t_engine *en, t_philo *philos, pid_t *proc_ids, int count);

#endif   /* INIT_BONUS_H */
