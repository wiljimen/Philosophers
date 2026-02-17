/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:41:00 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/17 21:41:16 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	usage(void)
{
	printf("Error\n");
	return (1);
}

static int	run(t_rules *r)
{
	if (!init_all(r))
		return (printf("init error\n"), 0);
	r->start_ms = now_ms();
	if (!start_threads(r))
		return (printf("thread error\n"), 0);
	join_threads(r);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	r;

	if (!parse_rules(&r, ac, av))
		return (usage());
	if (!run(&r))
		return (destroy_all(&r), 1);
	destroy_all(&r);
	return (0);
}
