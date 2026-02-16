/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 06:32:24 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/16 07:06:00 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	usage(void)
{
	printf("Usage: ./philo n t_die t_eat t_sleep [must_eat]\n");
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	r;

	if (!parse_rules(&r, ac, av))
		return (usage());

	if (!init_all(&r))
		return (printf("init error\n"), 1);

	r.start_ms = now_ms();
	printf("START: n=%d die=%ld eat=%ld sleep=%ld must=%d\n",
		r.n, r.t_die, r.t_eat, r.t_sleep, r.must_eat);

	if (!start_threads(&r))
		return (printf("thread error\n"), destroy_all(&r), 1);

	ms_sleep(1000);      /* test: deja correr 1s */
	set_stop(&r, 1);     /* test: forzamos stop */

	join_threads(&r);
	destroy_all(&r);
	printf("END\n");
	return (0);
}
