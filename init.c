/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:52:24 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/16 10:50:39 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_struct	*init_struct(int argc, char **argv, t_struct *p)
{
	int	i;

	i = -1;
	while (++i < p->nr_philos)
	{
		p->philos[i].x = i + 1;
		p->philos[i].die = atol(argv[2]);
		p->philos[i].eat = atol(argv[3]);
		p->philos[i].sleep = atol(argv[4]);
		p->philos[i].d_flag = 0;
		p->philos[i].time_last_meal = time_in_ms();
		if (argc == 6)
			p->philos[i].times_eat = atol(argv[5]);
	}
	if (p->philos[0].die < 0 || p->philos[0].eat < 0 || p->philos[0].sleep < 0)
	{
		free(p->philos);
		p->philos = NULL;
	}
	return (p);
}

int	init_mutex(t_struct *p)
{
	int	i;

	i = -1;
	p->forks = malloc(p->nr_philos * sizeof(pthread_mutex_t));
	if (!p->forks)
		return (1);
	while (++i < p->nr_philos)
	{
		if (pthread_mutex_init(&(p->forks[i]), NULL) != 0)
		{
			free(p->forks);
			return (1);
		}
	}
	i = -1;
	while (++i < p->nr_philos)
	{
		p->philos[i].l_fork = &p->forks[i];
		if (i == p->nr_philos - 1)
			p->philos[p->nr_philos - 1].r_fork = &(p->forks[0]);
		else
			p->philos[i].r_fork = &p->forks[i + 1];
	}
	return (0);
}
