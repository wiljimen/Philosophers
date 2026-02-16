/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 06:36:28 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 07:11:10 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	atoi_pos(const char *s, long *out)
{
	long	n;

	if (!s || !*s)
		return (0);
	n = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		n = n * 10 + (*s - '0');
		if (n > INT_MAX)
			return (0);
		s++;
	}
	*out = n;
	return (1);
}

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
	pthread_mutex_lock(&p->r->print_mtx);
	if (!get_stop(p->r))
		printf("%ld %d %s\n", since_start(p->r), p->id, msg);
	pthread_mutex_unlock(&p->r->print_mtx);
}