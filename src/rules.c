/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:46:26 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 16:46:28 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_stop(t_rules *r)
{
	int	v;

	pthread_mutex_lock(&r->stop_mtx);
	v = r->stop;
	pthread_mutex_unlock(&r->stop_mtx);
	return (v);
}

void	set_stop(t_rules *r, int v)
{
	pthread_mutex_lock(&r->stop_mtx);
	r->stop = v;
	pthread_mutex_unlock(&r->stop_mtx);
}

void	print_action(t_philo *p, const char *msg)
{
	if (get_stop(p->r))
		return ;
	pthread_mutex_lock(&p->r->print_mtx);
	if (!get_stop(p->r))
		printf("%ld %d %s\n", since_start(p->r), p->id, msg);
	pthread_mutex_unlock(&p->r->print_mtx);
}

void	print_death(t_rules *r, int id)
{
	pthread_mutex_lock(&r->print_mtx);
	printf("%ld %d died\n", since_start(r), id);
	pthread_mutex_unlock(&r->print_mtx);
}
