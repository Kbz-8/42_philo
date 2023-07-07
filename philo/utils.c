/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:52:22 by maldavid          #+#    #+#             */
/*   Updated: 2023/07/07 15:29:45 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned int	ft_atoi_check(const char *str, bool *check)
{
	long int	n;

	n = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if ((*str == '+' || *str == '-'))
		if (*str++ == '-')
			*check = true;
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	while (*str)
		if (*str++ != ' ')
			*check = true;
	if (n < -2147483648)
		return (-1);
	if (n > 2147483647)
		return (2147483647);
	return (n);
}

void	cout(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->noodles->mutex_print);
	time = timestamp() - philo->noodles->start_time;
	if (!end(philo->noodles) && time >= 0 && time <= LLONG_MAX)
		printf("%lld %zu %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->noodles->mutex_print);
}

void	mssleep(int ms, t_noodles *noodles)
{
	long	time;

	time = timestamp();
	while (timestamp() - time < ms && !end(noodles))
		usleep(ms / 10);
}
