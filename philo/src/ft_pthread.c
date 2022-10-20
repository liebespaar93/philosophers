/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:49:06 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/20 23:20:44 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_philo.h>
#include <sys/time.h>
#include <unistd.h>

void	ft_sleep(long long wait)
{
	wait += ft_timeval();
	while (ft_timeval() < wait)
		;
}

void	ft_right_handed(t_philo *philo, t_man *man)
{
	while (philo->time_to_die)
	{
		pthread_mutex_lock(&philo->forks[man->id]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		pthread_mutex_lock(
			&philo->forks[(man->id + 1) % philo->number_of_philosophers]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		ft_printf_mutex(man, ft_real_time(man), "is eating");
		man->eat_cnt++;
		ft_sleep(philo->time_to_eat);
		man->die_time = ft_real_time(man) + philo->time_to_die;
		pthread_mutex_unlock(
			&philo->forks[(man->id + 1) % philo->number_of_philosophers]);
		pthread_mutex_unlock(&philo->forks[man->id]);
		if (man->eat_cnt == philo->number_of_times_each_philosopher_must_eat)
			philo->end_eat++;
		ft_printf_mutex(man, ft_real_time(man), "is sleeping");
		ft_sleep(philo->time_to_sleep);
		ft_printf_mutex(man, ft_real_time(man), "is thinking");
	}
}

void	ft_left_handed(t_philo *philo, t_man *man)
{
	while (philo->time_to_die)
	{
		pthread_mutex_lock(
			&philo->forks[(man->id + 1) % philo->number_of_philosophers]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		pthread_mutex_lock(&philo->forks[man->id]);
		ft_printf_mutex(man, ft_real_time(man), "has taken a fork");
		ft_printf_mutex(man, ft_real_time(man), "is eating");
		man->eat_cnt++;
		ft_sleep(philo->time_to_eat);
		man->die_time = ft_real_time(man) + philo->time_to_die;
		pthread_mutex_unlock(&philo->forks[man->id]);
		pthread_mutex_unlock(
			&philo->forks[(man->id + 1) % philo->number_of_philosophers]);
		if (man->eat_cnt == philo->number_of_times_each_philosopher_must_eat)
			philo->end_eat++;
		ft_printf_mutex(man, ft_real_time(man), "is sleeping");
		ft_sleep(philo->time_to_sleep);
		ft_printf_mutex(man, ft_real_time(man), "is thinking");
	}
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
	return (0);
}
