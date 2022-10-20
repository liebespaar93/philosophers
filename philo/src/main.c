/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:44:58 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/20 23:05:16 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_philo.h>
#include <sys/time.h>
#include <unistd.h>

int	ft_hope_kill_man(t_philo *philo)
{
	int	i;

	philo->timeval = ft_timeval();
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		philo->man[i].create_time = ft_timeval();
		philo->man[i].die_time = \
			ft_real_time(&philo->man[i]) + philo->time_to_die;
		if (pthread_create(&(philo->man[i].thread_id), NULL, \
			ft_pthread, (void *)&philo->man[i]))
		{
			ft_free_philo(philo);
			return (0);
		}
		i++;
	}
	return (1);
}

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_detach(philo->man[i].thread_id);
		pthread_mutex_destroy(&philo->forks[i++]);
	}
	philo->dead = 0;
}

void	ft_work(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo->end_eat == philo->number_of_philosophers)
		{
			philo->time_to_die = 0;
			pthread_mutex_lock(&philo->printf);
			dest_mutex(philo);
			pthread_mutex_unlock(&philo->printf);
			return ;
		}
		if (ft_real_time(&philo->man[i]) > philo->man[i].die_time)
		{
			philo->time_to_die = 0;
			pthread_mutex_lock(&philo->printf);
			printf("%lldms	%d %s\n", \
			ft_real_time(&philo->man[i]), philo->man[i].id, "died");
			dest_mutex(philo);
			pthread_mutex_unlock(&philo->printf);
			return ;
		}
	}
}

int	ft_check(t_philo *philo)
{
	if (philo->end_eat >= philo->number_of_philosophers)
		return (1);
	return (0);
}

int	main(int ar, char *av[])
{
	t_philo	*philo;
	int		i;

	if (!(ar == 5 || ar == 6) && printf("input error!"))
		return (-1);
	philo = ft_philo_init(ar, av);
	if (!philo)
		return (-1);
	ft_hope_kill_man(philo);
	ft_work(philo);
	pthread_mutex_destroy(&philo->printf);
	ft_free_philo(philo);
}
