/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:36:10 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/05 00:12:53 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <pthread.h>

typedef struct s_philo	t_philo;
typedef struct s_man	t_man;

typedef struct s_philo
{
	long long		timeval;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				end_eat;
	int				dead;
	pthread_mutex_t	end_eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	*forks_mutex;
	t_man			*man;
}	t_philo;

typedef struct s_man
{
	int				id;
	long long		create_time;
	long long		die_time;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	pthread_mutex_t	man_mutex;
	pthread_mutex_t	die_time_mutex;
	pthread_t		thread_id;
	t_philo			*philo;
}	t_man;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		ft_sleep(long long wait);

t_philo		*ft_philo_init(t_philo *philo, int ar, char *av[]);
void		*ft_free_philo(t_philo *philo);

int			ft_thread_man(t_philo *philo);

void		ft_printf_mutex(t_man *man, long long time, char *str);

long long	ft_timeval(void);
long long	ft_real_time(t_man *man);

void		*ft_pthread(void *arg);

#endif