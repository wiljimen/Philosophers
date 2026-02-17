/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:41:16 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 16:41:17 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	atoi_pos(const char *s, long *out)
{
	long	n;
	int		i;

	i = 0;
	n = 0;
	if (!s || !s[0])
		return (0);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (n > (LONG_MAX - (s[i] - '0')) / 10)
			return (0);
		n = n * 10 + (s[i++] - '0');
	}
	if (s[i] != '\0' || n <= 0)
		return (0);
	*out = n;
	return (1);
}

static void	set_defaults(t_rules *r)
{
	r->must_eat = -1;
	r->stop = 0;
	r->forks = NULL;
	r->philos = NULL;
}

static int	fill(t_rules *r, int ac, char **av)
{
	long	v;

	set_defaults(r);
	if (ac != 5 && ac != 6)
		return (0);
	if (!atoi_pos(av[1], &v) || v > INT_MAX)
		return (0);
	r->n = (int)v;
	if (!atoi_pos(av[2], &r->t_die) || !atoi_pos(av[3], &r->t_eat))
		return (0);
	if (!atoi_pos(av[4], &r->t_sleep))
		return (0);
	if (ac == 6)
	{
		if (!atoi_pos(av[5], &v) || v > INT_MAX)
			return (0);
		r->must_eat = (int)v;
	}
	return (r->n > 0);
}

int	parse_rules(t_rules *r, int ac, char **av)
{
	return (fill(r, ac, av));
}
