/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:31:25 by maldavid          #+#    #+#             */
/*   Updated: 2023/07/07 15:32:56 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_noodles	*noodles;
	pthread_mutex_t		starving_mutex;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
	long				last_eat;
	size_t				eat_count;
	size_t				id;
	bool				is_eating;
	bool				starving;
}	t_philo;

typedef struct s_noodles
{
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_print;
	t_philo			*philos;
	int64_t			start_time;
	uint32_t		n_philos;
	uint32_t		n_eats;
	uint32_t		current_n_eats;
	int32_t			numbers_philos;
	int32_t			time_to_eat;
	int32_t			time_to_die;
	int32_t			time_to_sleep;
	bool			exit;
}	t_noodles;

long long		timestamp(void);
void			mssleep(int ms, t_noodles *noodles);
void			cout(t_philo *philo, char *str);
unsigned int	ft_atoi_check(const char *str, bool *check);
bool			init_noodles(t_noodles *noodles, char **av);
bool			init_philos(t_noodles *noodles);
bool			end(t_noodles *noodles);
bool			wait_for_philos(t_noodles *noodles);
void			destroy_noodles(t_noodles *noodles);
void			*brain(void *philo);

#endif
