/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:52:22 by maldavid          #+#    #+#             */
/*   Updated: 2023/06/30 14:35:12 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi_check(const char *str, bool *check)
{
	long int	n;
	int			neg;

	n = 0;
	neg = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if ((*str == '+' || *str == '-'))
		if (*str++ == '-')
			neg = ~(neg - 1);
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	while (*str)
		if (*str++ != ' ')
			*check = true;
	if (neg == -1 && n < -2147483648)
		return (0);
	if (neg && n < -2147483648)
		return (-1);
	return (n * neg);
}

void	log(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&(philo->noodles->mutex_print));
	time = timestamp() - philo->noodles->start_time;
	if (!philo->noodles->exit && time >= 0 && time <= LLONG_MAX)
		printf("%lld %zu %s\n", time, philo->id, str);
	pthread_mutex_unlock(&(philo->noodles->mutex_print));
}

void	ft_usleep(int ms)
{
	long	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}
