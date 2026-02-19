/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:47:01 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/19 13:27:54 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutexes(t_rules *r)
{
	if (pthread_mutex_init(&r->print_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&r->stop_mtx, NULL) != 0)
		return (0);
	return (1);
}

int	init_arrays(t_rules *r)
{
	r->forks = malloc(sizeof(pthread_mutex_t) * r->n);
	r->philos = malloc(sizeof(t_philo) * r->n);
	if (!r->forks || !r->philos)
		return (0);
	return (1);
}

int	init_forks(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n)
	{
		if (pthread_mutex_init(&r->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_philos(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n)
	{
		r->philos[i].id = i + 1;
		r->philos[i].r = r;
		r->philos[i].l_fork = &r->forks[i];
		r->philos[i].r_fork = &r->forks[(i + 1) % r->n];
		r->philos[i].last_meal_ms = 0;
		r->philos[i].meals = 0;
		if (pthread_mutex_init(&r->philos[i].meal_mtx, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
