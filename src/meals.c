/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:47:32 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 16:54:32 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	meal_update(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal_ms = now_ms();
	p->meals++;
	pthread_mutex_unlock(&p->meal_mtx);
}

long	meal_get_last(t_philo *p)
{
	long	v;

	pthread_mutex_lock(&p->meal_mtx);
	v = p->last_meal_ms;
	pthread_mutex_unlock(&p->meal_mtx);
	return (v);
}

int	meal_get_count(t_philo *p)
{
	int	v;

	pthread_mutex_lock(&p->meal_mtx);
	v = p->meals;
	pthread_mutex_unlock(&p->meal_mtx);
	return (v);
}
