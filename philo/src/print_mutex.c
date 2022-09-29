#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_philo.h>
#include <sys/time.h>

void	ft_printf_mutex(t_man *man, long long time, char *str)
{
	pthread_mutex_lock(&man->philo->printf);
	printf("%lld	%d %s\n", time, man->id, str);
	pthread_mutex_unlock(&man->philo->printf);
}
