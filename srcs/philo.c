/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:37:42 by maldavid          #+#    #+#             */
/*   Updated: 2023/06/30 15:48:26 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	mssleep(p->noodles->time_to_die + 1);
	pthread_mutex_lock(&p->noodles->mutex_eat);
	pthread_mutex_lock(&p->noodles->mutex_exit);
	if (!end(p->noodles) && \
		timestamp() - p->last_eat >= p->noodles->time_to_die)
	{
		cout(p, " died");
		p->noodles->exit = true;
	}
	pthread_mutex_unlock(&p->noodles->mutex_eat);
	pthread_mutex_unlock(&p->noodles->mutex_exit);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	cout(philo, " has taken a fork");
	if (philo->noodles->n_philos == 1)
	{
		mssleep(philo->noodles->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	cout(philo, " has taken a fork");
}

void	eat(t_philo *philo)
{
	cout(philo, " is eating");
	pthread_mutex_lock(&philo->noodles->mutex_eat);
	philo->last_eat = timestamp();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->noodles->mutex_eat);
	mssleep(philo->noodles->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	cout(philo, " is sleeping");
	mssleep(philo->noodles->time_to_sleep);
	cout(philo, " is thinking");
}

void	*brain(void	*philo)
{
	t_philo		*p;
	pthread_t	death_thread;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		mssleep(p->noodles->time_to_eat / 10);
	while (!end(p->noodles))
	{
		pthread_create(&death_thread, NULL, check_death, philo);
		take_fork(p);
		eat(p);
		pthread_detach(death_thread);
		if (p->eat_count == p->noodles->n_eats)
		{
			pthread_mutex_lock(&p->noodles->mutex_exit);
			p->noodles->current_n_eats++;
			if (p->noodles->current_n_eats == p->noodles->n_philos)
				p->noodles->exit = true;
			pthread_mutex_unlock(&p->noodles->mutex_exit);
			return (NULL);
		}
	}
	return (NULL);
}
