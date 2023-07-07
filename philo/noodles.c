/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noodles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:55:47 by maldavid          #+#    #+#             */
/*   Updated: 2023/07/07 13:49:14 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	init_philos(t_noodles *noodles)
{
	int	i;

	noodles->start_time = timestamp();
	i = 0;
	while (i < noodles->n_philos)
	{
		noodles->philos[i].id = i;
		noodles->philos[i].starving = true;
		noodles->philos[i].last_eat = 0;
		noodles->philos[i].r_fork = NULL;
		noodles->philos[i].noodles = noodles;
		noodles->philos[i].eat_count = 0;
		pthread_mutex_init(&noodles->philos[i].l_fork, NULL);
		pthread_mutex_init(&noodles->philos[i].starving_mutex, NULL);
		if (i == noodles->n_philos - 1)
			noodles->philos[i].r_fork = &noodles->philos[0].l_fork;
		else
			noodles->philos[i].r_fork = &noodles->philos[i + 1].l_fork;
		i++;
	}
	return (true);
}

bool	wait_for_philos(t_noodles *noodles)
{
	int	i;

	i = 0;
	while (i < noodles->n_philos)
	{
		if (pthread_create(&noodles->philos[i].thread, NULL, brain, \
							&noodles->philos[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < noodles->n_philos)
	{
		if (pthread_join(noodles->philos[i].thread, NULL))
			return (false);
		i++;
	}
	return (true);
}

bool	end(t_noodles *noodles)
{
	pthread_mutex_lock(&noodles->mutex_dead);
	if (noodles->exit)
	{
		pthread_mutex_unlock(&noodles->mutex_dead);
		return (true);
	}
	pthread_mutex_unlock(&noodles->mutex_dead);
	return (false);
}

bool	init_noodles(t_noodles *noodles, char **av)
{
	bool	check;

	check = false;
	memset(noodles, 0, sizeof(t_noodles));
	noodles->n_philos = ft_atoi_check(av[1], &check);
	noodles->time_to_die = ft_atoi_check(av[2], &check);
	noodles->time_to_eat = ft_atoi_check(av[3], &check);
	noodles->time_to_sleep = ft_atoi_check(av[4], &check);
	if (av[5] != NULL)
		noodles->n_eats = ft_atoi_check(av[5], &check);
	if (av[5] != NULL && noodles->n_eats == 0)
		return (false);
	if (check)
		return (false);
	noodles->philos = malloc(noodles->n_philos * sizeof(t_philo));
	if (noodles->philos == NULL)
	{
		write(2, "malloc failed in noodles creation\n", 34);
		return (false);
	}
	pthread_mutex_init(&noodles->mutex_eat, NULL);
	pthread_mutex_init(&noodles->mutex_dead, NULL);
	pthread_mutex_init(&noodles->mutex_print, NULL);
	return (true);
}

void	destroy_noodles(t_noodles *noodles)
{
	int	i;

	i = 0;
	while (i < noodles->n_philos)
	{
		pthread_mutex_destroy(noodles->philos[i].r_fork);
		i++;
	}
	free(noodles->philos);
	pthread_mutex_destroy(&noodles->mutex_eat);
	pthread_mutex_destroy(&noodles->mutex_dead);
	pthread_mutex_destroy(&noodles->mutex_print);
}
