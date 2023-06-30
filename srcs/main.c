/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:30:39 by maldavid          #+#    #+#             */
/*   Updated: 2023/06/29 22:03:36 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_noodles	noodles;

	if (ac != 5 && ac != 6)
		return (1);
	if (!init_noodles(&noodles, av))
		return (1);
	if (!init_philos(&noodles) || !wait_for_philos(&noodles))
	{
		destroy_noodles(&noodles);
		return (1);
	}
	destroy_noodles(&noodles);
	return (0);
}
