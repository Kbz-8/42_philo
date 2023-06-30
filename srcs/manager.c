/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:55:47 by maldavid          #+#    #+#             */
/*   Updated: 2023/06/30 02:08:29 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	init_all_philos(t_manager *man)
{
	size_t	i;

	i = 0;
	while (i <= man->numbers_philos)
	{
		if (i < man->numbers_philos)
		{
			if (pthread_create(&man->philos[i].thread, NULL, routine, &man->philos[i]))
				return (false);
		}
		if (pthread_mutex_init(&man->forks[i], NULL))
			return (false);
		i++;
	}
	return (true);
}
R
void	init_manager(t_manager *manager)
{
	manager->philos = malloc(sizeof(t_philo) * manager->numbers_philos);
	manager->forks = malloc(sizeof(pthread_mutex_t) * (manager->numbers_philos + 1));
	init_all_philos(manager);
}
