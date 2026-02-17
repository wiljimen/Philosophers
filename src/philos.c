/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:47:55 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/17 21:23:21 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	stagger(t_philo *p)
{
	if (p->id % 2 == 0)
		usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	stagger(p);
	while (!get_stop(p->r))
	{
		if (!take_forks(p))
			return (smart_sleep(p->r, p->r->t_die + 5), NULL);
		meal_update(p);
		print_action(p, "is eating");
		smart_sleep(p->r, p->r->t_eat);
		drop_forks(p);
		print_action(p, "is sleeping");
		smart_sleep(p->r, p->r->t_sleep);
		print_action(p, "is thinking");
		usleep(200);
	}
	return (NULL);
}

int	take_forks(t_philo *p)
{
	if (p->id % 2)
	{
		pthread_mutex_lock(p->l_fork);
		print_action(p, "has taken a fork");
		if (p->l_fork == p->r_fork)
			return (0);
		pthread_mutex_lock(p->r_fork);
		print_action(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->r_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(p->l_fork);
		print_action(p, "has taken a fork");
	}
	return (1);
}

void	drop_forks(t_philo *p)
{
	if (p->l_fork == p->r_fork)
		return ((void)pthread_mutex_unlock(p->l_fork));
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}
