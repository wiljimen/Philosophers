/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:47:01 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 16:47:02 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_mutexes(t_rules *r)
{
	if (pthread_mutex_init(&r->print_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&r->stop_mtx, NULL) != 0)
		return (0);
	return (1);
}

static int	init_arrays(t_rules *r)
{
	r->forks = malloc(sizeof(pthread_mutex_t) * r->n);
	r->philos = malloc(sizeof(t_philo) * r->n);
	if (!r->forks || !r->philos)
		return (0);
	return (1);
}

static int	init_forks(t_rules *r)
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

static int	init_philos(t_rules *r)
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
