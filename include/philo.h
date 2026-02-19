/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:21:29 by wiljimen          #+#    #+#             */
/*   Updated: 2026/02/19 13:29:08 by wiljimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	long			last_meal_ms;
	int				meals;
	pthread_mutex_t	meal_mtx;

	t_rules			*r;
}					t_philo;

typedef struct s_rules
{
	int				n;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				must_eat;

	long			start_ms;
	int				stop;

	pthread_mutex_t	print_mtx;
	pthread_mutex_t	stop_mtx;

	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor_th;
}					t_rules;

/*----PARSE----*/
int		parse_rules(t_rules *r, int ac, char **av);

/*----TIMEs----*/
long	now_ms(void);
long	since_start(t_rules *r);
void	smart_sleep(t_rules *r, long ms);

/*----PHILO_STATES----*/
int		get_stop(t_rules *r);
void	set_stop(t_rules *r, int v);
void	print_action(t_philo *p, const char *msg);
void	print_death(t_rules *r, int id);

/*----START----*/
int		init_mutexes(t_rules *r);
int		init_arrays(t_rules *r);
int		init_forks(t_rules *r);
int		init_philos(t_rules *r);
int		init_all(t_rules *r);
void	destroy_all(t_rules *r);

/*----MEALS----*/
void	meal_inc(t_philo *p);
void	meal_set_last(t_philo *p, long ms);
long	meal_get_last(t_philo *p);
int		meal_get_count(t_philo *p);

/*----FORKS----*/
int		take_forks(t_philo *p);
void	drop_forks(t_philo *p);

/*----PHILO AND THREADS----*/
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
int		start_threads(t_rules *r);
int		join_threads(t_rules *r);

#endif
