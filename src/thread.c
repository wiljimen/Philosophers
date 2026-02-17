/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:49:08 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 16:54:53 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	all_ate(t_rules *r)
{
	int	i;

	if (r->must_eat < 0)
		return (0);
	i = 0;
	while (i < r->n)
		if (meal_get_count(&r->philos[i++]) < r->must_eat)
			return (0);
	return (1);
}

static int	check_death(t_rules *r)
{
	int		i;
	long	last;

	i = 0;
	while (i < r->n && !get_stop(r))
	{
		last = meal_get_last(&r->philos[i]);
		if (now_ms() - last > r->t_die)
			return (set_stop(r, 1), print_death(r, r->philos[i].id), 1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_rules	*r;

	r = (t_rules *)arg;
	while (!get_stop(r))
	{
		if (check_death(r))
			return (NULL);
		if (!get_stop(r) && all_ate(r))
			return (set_stop(r, 1), NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_threads(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n)
	{
		pthread_mutex_lock(&r->philos[i].meal_mtx);
		r->philos[i].last_meal_ms = r->start_ms;
		r->philos[i].meals = 0;
		pthread_mutex_unlock(&r->philos[i].meal_mtx);
		if (pthread_create(&r->philos[i].th, NULL, philo_routine, &r->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&r->monitor_th, NULL, monitor_routine, r))
		return (0);
	return (1);
}

int	join_threads(t_rules *r)
{
	int	i;

	pthread_join(r->monitor_th, NULL);
	i = 0;
	while (i < r->n)
		pthread_join(r->philos[i++].th, NULL);
	return (1);
}
