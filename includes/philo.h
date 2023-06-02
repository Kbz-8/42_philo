/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:31:25 by maldavid          #+#    #+#             */
/*   Updated: 2023/06/02 19:40:52 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
}	t_state;

typedef struct s_philo
{
	pthread_t	thread;
	t_state		state;
}	t_philo;

typedef struct s_manager
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int32_t			numbers_philos;
	int32_t			time_to_eat;
	int32_t			time_to_die;
	int32_t			time_to_sleep;
}	t_manager;

#endif
