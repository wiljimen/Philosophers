/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:19:50 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/19 13:21:22 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_all(t_rules *r)
{
	if (!init_mutexes(r))
		return (0);
	if (!init_arrays(r))
		return (0);
	if (!init_forks(r))
		return (0);
	if (!init_philos(r))
		return (0);
	return (1);
}

void	destroy_all(t_rules *r)
{
	int	i;

	i = 0;
	if (r->philos)
		while (i < r->n)
			pthread_mutex_destroy(&r->philos[i++].meal_mtx);
	i = 0;
	if (r->forks)
		while (i < r->n)
			pthread_mutex_destroy(&r->forks[i++]);
	pthread_mutex_destroy(&r->print_mtx);
	pthread_mutex_destroy(&r->stop_mtx);
	free(r->forks);
	free(r->philos);
}
