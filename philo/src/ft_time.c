/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:44:29 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/05 00:44:25 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_philo.h>
#include <sys/time.h>

long long	ft_timeval(void)
{
	struct timeval	time;
	long long		timeval;

	gettimeofday(&time, NULL);
	timeval = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timeval);
}

long long	ft_real_time(t_man *man)
{
	return (ft_timeval() - man->create_time);
}

void	ft_sleep(long long wait)
{
	wait += ft_timeval();
	while (ft_timeval() < wait)
		usleep(100);
}
