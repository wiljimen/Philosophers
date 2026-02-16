/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 07:00:51 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 07:01:04 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parse_rules(t_rules *r, int ac, char **av)
{
	long	tmp;

	if (!(ac == 5 || ac == 6))
		return (0);
	if (!atoi_pos(av[1], &tmp) || tmp <= 0)
		return (0);
	r->n = (int)tmp;
	if (!atoi_pos(av[2], &tmp) || tmp <= 0)
		return (0);
	r->t_die = tmp;
	if (!atoi_pos(av[3], &tmp) || tmp <= 0)
		return (0);
	r->t_eat = tmp;
	if (!atoi_pos(av[4], &tmp) || tmp <= 0)
		return (0);
	r->t_sleep = tmp;
	r->must_eat = -1;
	if (ac == 6)
	{
		if (!atoi_pos(av[5], &tmp) || tmp <= 0)
			return (0);
		r->must_eat = (int)tmp;
	}
	return (1);
}
