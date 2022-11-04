/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:49:06 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/05 00:46:59 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_philo.h>
#include <sys/time.h>
#include <unistd.h>

int	ft_check_dead(t_philo *philo)
{
	int	result;

	result = 1;
	pthread_mutex_lock(&philo->dead_mutex);
	if (!philo->dead)
		result = 0;
	pthread_mutex_unlock(&philo->dead_mutex);
	return (result);
}

void	ft_eating(t_philo *philo, t_man *man)
{
	pthread_mutex_lock(&man->die_time_mutex);
	man->die_time = ft_timeval() + philo->time_to_die;
	pthread_mutex_unlock(&man->die_time_mutex);
	ft_printf_mutex(man, ft_real_time(man), "is eating");
	ft_sleep(philo->time_to_eat);
	if (++man->eat_cnt == philo->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->end_eat_mutex);
		philo->end_eat++;
		pthread_mutex_unlock(&philo->end_eat_mutex);
	}
}

void	ft_right_handed(t_philo *philo, t_man *man)
{
	pthread_mutex_lock(&man->man_mutex);
	while (ft_check_dead(philo))
	{
		pthread_mutex_lock(&philo->forks_mutex[man->right_fork]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		pthread_mutex_lock(&philo->forks_mutex[man->left_fork]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		ft_eating(philo, man);
		pthread_mutex_unlock(&philo->forks_mutex[man->left_fork]);
		pthread_mutex_unlock(&philo->forks_mutex[man->right_fork]);
		ft_printf_mutex(man, ft_real_time(man), "is sleeping");
		ft_sleep(philo->time_to_sleep);
		ft_printf_mutex(man, ft_real_time(man), "is thinking");
	}
	pthread_mutex_unlock(&man->man_mutex);
}

void	ft_left_handed(t_philo *philo, t_man *man)
{
	pthread_mutex_lock(&man->man_mutex);
	while (ft_check_dead(philo))
	{
		pthread_mutex_lock(&philo->forks_mutex[man->left_fork]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		pthread_mutex_lock(&philo->forks_mutex[man->right_fork]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		ft_eating(philo, man);
		pthread_mutex_unlock(&philo->forks_mutex[man->right_fork]);
		pthread_mutex_unlock(&philo->forks_mutex[man->left_fork]);
		ft_printf_mutex(man, ft_real_time(man), "is sleeping");
		ft_sleep(philo->time_to_sleep);
		ft_printf_mutex(man, ft_real_time(man), "is thinking");
	}
	pthread_mutex_unlock(&man->man_mutex);
}

void	*ft_pthread(void *arg)
{
	t_man	*man;
	t_philo	*philo;

	man = (t_man *)arg;
	philo = man->philo;
	if (man->id % 2)
		ft_right_handed(philo, man);
	else
		ft_left_handed(philo, man);
	return (NULL);
}
