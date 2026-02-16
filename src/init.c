/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 07:09:35 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 07:09:48 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_all(t_rules *r)
{
	int	i;

	r->stop = 0;
	r->forks = NULL;
	r->philos = NULL;
	if (pthread_mutex_init(&r->print_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&r->stop_mtx, NULL) != 0)
		return (0);
	r->forks = malloc(sizeof(pthread_mutex_t) * r->n);
	r->philos = malloc(sizeof(t_philo) * r->n);
	if (!r->forks || !r->philos)
		return (0);
	i = 0;
	while (i < r->n)
	{
		if (pthread_mutex_init(&r->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < r->n)
	{
		r->philos[i].id = i + 1;
		r->philos[i].r = r;
		r->philos[i].meals = 0;
		r->philos[i].last_meal_ms = 0;
		r->philos[i].l_fork = &r->forks[i];
		r->philos[i].r_fork = &r->forks[(i + 1) % r->n];
		i++;
	}
	return (1);
}

void	destroy_all(t_rules *r)
{
	int	i;

	if (r->forks)
	{
		i = 0;
		while (i < r->n)
		{
			pthread_mutex_destroy(&r->forks[i]);
			i++;
		}
		free(r->forks);
	}
	pthread_mutex_destroy(&r->print_mtx);
	pthread_mutex_destroy(&r->stop_mtx);
	free(r->philos);
}
