/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 07:04:26 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 07:04:37 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	p->last_meal_ms = now_ms();
	if (p->id % 2 == 0)
		usleep(1000);

	while (!get_stop(p->r))
	{
		pthread_mutex_lock(p->l_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print_action(p, "has taken a fork");

		print_action(p, "is eating");
		p->last_meal_ms = now_ms();
		p->meals++;
		ms_sleep(p->r->t_eat);

		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(p->l_fork);

		print_action(p, "is sleeping");
		ms_sleep(p->r->t_sleep);

		print_action(p, "is thinking");
	}
	return (NULL);
}

int	start_threads(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n)
	{
		if (pthread_create(&r->philos[i].th, NULL,
				philo_routine, &r->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	join_threads(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n)
	{
		pthread_join(r->philos[i].th, NULL);
		i++;
	}
	return (1);
}
