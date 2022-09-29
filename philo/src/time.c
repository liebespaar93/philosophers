#include <unistd.h>
#include <ft_philo.h>
#include <sys/time.h>

long long	ft_timeval()
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
