
int	ft_isdigit(int c)
{
	if (0x30 <= c && c <= 0x39)
		return (1);
	return (0);
}

int	ft_atoi_overflow(long sign);

int	ft_atoi(const char *str)
{
	int		num;
	long	sign;

	num = 0;
	sign = 1;
	while ((0x09 <= *str && *str <= 0x0d) || *str == 0x20)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (num > num * 10)
			return (ft_atoi_overflow(sign));
		num = num * 10 + (*str - 0x30);
		str++;
	}
	return ((int)(num * sign));
}

int	ft_atoi_overflow(long sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}