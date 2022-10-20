/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:48:27 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/20 12:09:12 by kyoulee          ###   ########.fr       */
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
		i++;
	}
	return (philo->man);
}

pthread_mutex_t	*ft_fork_init(t_philo *philo, int len)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * len);
	if (!philo->forks)
		return (NULL);
	while (i < len)
		pthread_mutex_init(&philo->forks[i++], NULL);
	return (philo->forks);
}

void	*ft_free_philo(t_philo *philo)
{
	if (philo->forks)
		free(philo->forks);
	if (philo->man)
		free(philo->man);
	free(philo);
	return (NULL);
}

t_philo	*ft_philo_init(int ar, char *av[])
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->end_eat = 0;
	philo->number_of_philosophers = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->dead = 1;
	if (philo->number_of_philosophers <= 0 || philo->time_to_die <= 0 \
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
		return (ft_free_philo(philo));
	if (ar == 6)
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	pthread_mutex_init(&philo->printf, NULL);
	if (!ft_fork_init(philo, philo->number_of_philosophers) || \
		!ft_man_init(philo, philo->number_of_philosophers))
		return (ft_free_philo(philo));
	return (philo);
}
