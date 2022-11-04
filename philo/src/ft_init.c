/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:48:27 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/05 01:03:25 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_philo.h>
#include <sys/time.h>

t_man	*ft_man_init(t_philo *philo, int len)
{
	int	i;

	i = 0;
	philo->man = malloc(sizeof(t_man) * len);
	if (!philo->man)
		return (NULL);
	while (i < len)
	{
		philo->man[i].id = i;
		philo->man[i].left_fork = i;
		philo->man[i].right_fork = (i + 1) % len;
		philo->man[i].eat_cnt = 0;
		philo->man[i].philo = philo;
		pthread_mutex_init(&philo->man[i].man_mutex, NULL);
		pthread_mutex_init(&philo->man[i].die_time_mutex, NULL);
		i++;
	}
	return (philo->man);
}

pthread_mutex_t	*ft_fork_init(t_philo *philo, int len)
{
	int	i;

	i = 0;
	philo->forks_mutex = malloc(sizeof(pthread_mutex_t) * len);
	if (!philo->forks_mutex)
		return (NULL);
	while (i < len)
		pthread_mutex_init(&philo->forks_mutex[i++], NULL);
	return (philo->forks_mutex);
}

void	*ft_free_philo(t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->end_eat_mutex);
	pthread_mutex_destroy(&philo->dead_mutex);
	pthread_mutex_destroy(&philo->printf_mutex);
	if (philo->forks_mutex)
	{
		i = 0;
		while (i < philo->number_of_philosophers)
			pthread_mutex_destroy(&philo->forks_mutex[i++]);
		free(philo->forks_mutex);
	}
	if (philo->man)
	{
		i = 0;
		while (i < philo->number_of_philosophers)
		{
			pthread_mutex_destroy(&philo->man[i].man_mutex);
			pthread_mutex_destroy(&philo->man[i].die_time_mutex);
			i++;
		}
		free(philo->man);
	}
	return (NULL);
}

t_philo	*ft_philo_init(t_philo *philo, int ar, char *av[])
{
	philo->end_eat = 0;
	philo->number_of_philosophers = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->dead = 1;
	if (ar == 6)
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	if ((philo->number_of_philosophers <= 0 || philo->time_to_die <= 0 \
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0 \
		|| philo->number_of_times_each_philosopher_must_eat < 0) \
		&& printf("input num error!"))
		return (NULL);
	if (pthread_mutex_init(&philo->end_eat_mutex, NULL) || \
		pthread_mutex_init(&philo->dead_mutex, NULL) || \
		pthread_mutex_init(&philo->printf_mutex, NULL) || \
		!ft_fork_init(philo, philo->number_of_philosophers) || \
		!ft_man_init(philo, philo->number_of_philosophers))
		return (ft_free_philo(philo));
	return (philo);
}
