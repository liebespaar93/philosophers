/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:44:58 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/05 00:51:46 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ft_philo.h>

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (philo->man[i].id % 2)
		{
			pthread_mutex_unlock(&philo->forks_mutex[philo->man[i].left_fork]);
			pthread_mutex_unlock(&philo->forks_mutex[philo->man[i].right_fork]);
		}
		else
		{
			pthread_mutex_unlock(&philo->forks_mutex[philo->man[i].right_fork]);
			pthread_mutex_unlock(&philo->forks_mutex[philo->man[i].left_fork]);
		}
		pthread_mutex_lock(&philo->man[i].man_mutex);
		pthread_detach(philo->man[i].thread_id);
		pthread_mutex_unlock(&philo->man[i].man_mutex);
		i++;
	}
}

int	ft_all_eat(t_philo *philo)
{
	int	eat;

	pthread_mutex_lock(&philo->end_eat_mutex);
	eat = philo->end_eat;
	pthread_mutex_unlock(&philo->end_eat_mutex);
	if (eat == philo->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->dead_mutex);
		philo->dead = 0;
		pthread_mutex_unlock(&philo->dead_mutex);
		return (1);
	}
	return (0);
}

int	ft_work(t_philo *philo)
{
	int			i;
	long long	time;

	i = 0;
	while (1)
	{
		if (ft_all_eat(philo))
			return (1);
		pthread_mutex_lock(&philo->man[i].die_time_mutex);
		time = philo->man[i].die_time;
		pthread_mutex_unlock(&philo->man[i].die_time_mutex);
		if (ft_timeval() > time)
		{
			pthread_mutex_lock(&philo->printf_mutex);
			pthread_mutex_lock(&philo->dead_mutex);
			philo->dead = 0;
			pthread_mutex_unlock(&philo->dead_mutex);
			printf("%lld	%d %s\n", \
				ft_real_time(&philo->man[i]), philo->man[i].id, "died");
			pthread_mutex_unlock(&philo->printf_mutex);
			return (0);
		}
		if (++i >= philo->number_of_philosophers)
			i = 0;
	}
}

int	main(int ar, char *av[])
{
	t_philo	philo;

	ft_bzero(&philo, sizeof(t_philo));
	if (!(ar == 5 || ar == 6) && printf("input error!"))
		return (-1);
	if (!ft_philo_init(&philo, ar, av))
		return (0);
	if (!ft_thread_man(&philo))
		return (0);
	ft_work(&philo);
	dest_mutex(&philo);
	ft_free_philo(&philo);
	return (0);
}
