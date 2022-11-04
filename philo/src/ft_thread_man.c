/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_man.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:37:49 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/04 23:48:17 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

int	ft_thread_man(t_philo *philo)
{
	int	i;

	philo->timeval = ft_timeval();
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		philo->man[i].create_time = ft_timeval();
		philo->man[i].die_time = ft_timeval() + philo->time_to_die;
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
