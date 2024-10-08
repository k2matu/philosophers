/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:52:24 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 22:16:57 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_struct(int argc, t_struct *p)
{
	int	i;

	i = -1;
	while (++i < p->nr_philos)
	{
		p->philos[i].nr_philos = p->nr_philos;
		p->philos[i].x = i + 1;
		p->philos[i].die = p->die;
		p->philos[i].eat = p->eat;
		p->philos[i].sleep = p->sleep;
		p->philos[i].d_flag = &p->dead_flag;
		p->philos[i].time_last_meal = time_in_ms();
		p->philos[i].time_start = time_in_ms();
		if (argc == 6)
			p->philos[i].times_eat = p->times_eat;
		else
			p->philos[i].times_eat = -1;
	}
}

static void	lock_forks(t_struct *p)
{
	int	i;

	i = -1;
	if (p->nr_philos == 1)
		p->philos[0].l_fork = &p->forks[0];
	else
	{
		while (++i < p->nr_philos)
		{
			p->philos[i].meal_lock = &p->meal_lock;
			p->philos[i].write_lock = &p->write_lock;
			p->philos[i].dead_lock = &p->dead_lock;
			p->philos[i].l_fork = &p->forks[i];
			if (i == p->nr_philos - 1)
				p->philos[p->nr_philos - 1].r_fork = &(p->forks[0]);
			else
				p->philos[i].r_fork = &p->forks[i + 1];
		}
	}
}

static int	init_mutex(t_struct *p)
{
	int	i;

	i = -1;
	p->forks = malloc((p->nr_philos) * sizeof(pthread_mutex_t));
	if (!p->forks)
	{
		free(p->philos);
		return (error_msg("Malloc failed", 0));
	}
	while (++i < p->nr_philos)
	{
		if (pthread_mutex_init(&(p->forks[i]), NULL) != 0)
		{
			cleanup_resources(p, i);
			error_msg("Mutex init failed", 0);
		}
	}
	lock_forks(p);
	return (TRUE);
}

int	init(int argc, t_struct *p)
{
	if (pthread_mutex_init(&(p->meal_lock), NULL) != 0)
	{
		free(p->philos);
		error_msg("Mutex init failed", FALSE);
	}
	if (pthread_mutex_init(&(p->write_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(p->meal_lock));
		free(p->philos);
		error_msg("Mutex init failed", FALSE);
	}
	if (pthread_mutex_init(&(p->dead_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(p->meal_lock));
		pthread_mutex_destroy(&(p->write_lock));
		free(p->philos);
		error_msg("Mutex init failed", FALSE);
	}
	if (!init_mutex(p))
		return (FALSE);
	init_struct(argc, p);
	return (TRUE);
}
