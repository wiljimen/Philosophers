/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:41:52 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/19 13:20:11 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	since_start(t_rules *r)
{
	return (now_ms() - r->start_ms);
}

void	smart_sleep(t_rules *r, long ms)
{
	long	start;

	start = now_ms();
	while (!get_stop(r) && (now_ms() - start) < ms)
		usleep(300);
}
