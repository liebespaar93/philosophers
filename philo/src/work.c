/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:44:24 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/19 12:44:25 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_philo.h>
#include <sys/time.h>

int	ft_sleeping(t_man *man)
{
	long long	sleep_time;
	long long	start_sleep_time;
	long long	now_time;

	sleep_time = (long long)(man->philo->time_to_sleep);
	start_sleep_time = ft_timeval();
	now_time = start_sleep_time;
	ft_printf_mutex(man, ft_real_time(man), "is sleeping");
	while (man->die_time > now_time)
	{
		now_time = ft_timeval();
		if ((now_time - start_sleep_time) >= sleep_time)
			return (1);
	}
	return (0);
}

int	ft_eating(t_man *man)
{
	long long	eat_time;
	long long	start_eat_time;
	long long	now_time;

	eat_time = (long long)(man->philo->time_to_eat);
	start_eat_time = ft_timeval();
	now_time = start_eat_time;
	ft_printf_mutex(man, ft_real_time(man), "is eating");
	while (eat_time > now_time)
	{
		now_time = ft_timeval();
		if ((now_time - start_eat_time) >= eat_time)
			return (1);
	}
	ft_printf_mutex(man, ft_real_time(man), "is eated");
	return (0);
}
