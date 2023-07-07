/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:37:42 by maldavid          #+#    #+#             */
/*   Updated: 2023/07/07 13:58:25 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	check_starvation(t_philo *philo)
{
	pthread_mutex_lock(&philo->starving_mutex);
	if (philo->starving)
	{
		pthread_mutex_unlock(&philo->starving_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->starving_mutex);
	return (false);
}

void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (!end(p->noodles))
	{
		if (!check_starvation(p))
			continue ;
		mssleep(p->noodles->time_to_die + 1, p->noodles);
		pthread_mutex_lock(&p->noodles->mutex_eat);
		if (!end(p->noodles) && \
			timestamp() - p->last_eat >= p->noodles->time_to_die)
		{
			cout(p, " died");
			pthread_mutex_lock(&p->noodles->mutex_dead);
			p->noodles->exit = true;
			pthread_mutex_unlock(&p->noodles->mutex_dead);
		}
		pthread_mutex_unlock(&p->noodles->mutex_eat);
		pthread_mutex_lock(&p->starving_mutex);
		p->starving = false;
		pthread_mutex_unlock(&p->starving_mutex);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	cout(philo, " has taken a fork");
	if (philo->noodles->n_philos == 1)
	{
		mssleep(philo->noodles->time_to_die * 2, philo->noodles);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	cout(philo, " has taken a fork");
	cout(philo, " is eating");
	pthread_mutex_lock(&philo->noodles->mutex_eat);
	philo->last_eat = timestamp();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->noodles->mutex_eat);
	mssleep(philo->noodles->time_to_eat, philo->noodles);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	cout(philo, " is sleeping");
	mssleep(philo->noodles->time_to_sleep, philo->noodles);
	cout(philo, " is thinking");
}

void	*brain(void	*philo)
{
	t_philo		*p;
	pthread_t	death_thread;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		mssleep(p->noodles->time_to_eat / 10, p->noodles);
	pthread_create(&death_thread, NULL, check_death, philo);
	while (!end(p->noodles))
	{
		pthread_mutex_lock(&p->starving_mutex);
		p->starving = true;
		pthread_mutex_unlock(&p->starving_mutex);
		eat(p);
		if (p->eat_count == p->noodles->n_eats)
		{
			pthread_mutex_lock(&p->noodles->mutex_dead);
			p->noodles->current_n_eats++;
			if (p->noodles->current_n_eats == p->noodles->n_philos)
				p->noodles->exit = true;
			pthread_mutex_unlock(&p->noodles->mutex_dead);
			break ;
		}
	}
	pthread_join(death_thread, NULL);
	return (NULL);
}
