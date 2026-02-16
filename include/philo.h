#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_rules	t_rules;
typedef struct s_philo	t_philo;

struct s_rules
{
	int				n;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				must_eat; /* -1 si no se pasa */

	long			start_ms;
	int				stop;

	pthread_mutex_t	print_mtx;
	pthread_mutex_t	stop_mtx;

	pthread_mutex_t	*forks;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	pthread_t		th;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	long			last_meal_ms;
	int				meals;

	t_rules			*r;
};

/* parse */
int		parse_rules(t_rules *r, int ac, char **av);

/* time */
long	now_ms(void);
long	since_start(t_rules *r);
void	ms_sleep(long ms);

/* init */
int		init_all(t_rules *r);
void	destroy_all(t_rules *r);

/* threads */
void	*philo_routine(void *arg);
int		start_threads(t_rules *r);
int		join_threads(t_rules *r);

/* utils */

int		ft_atoi(const char *str);
int		atoi_pos(const char *s, long *out);
int		get_stop(t_rules *r);
void	set_stop(t_rules *r, int v);
void	print_action(t_philo *p, const char *msg);


#endif
