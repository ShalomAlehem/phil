/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:32:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/09/30 11:56:29 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

#include "philosophers.h"

void	monitor_death(t_config *config)
{
	int				i;
	t_ph			*ph;
	struct timeval	now;
	long			delta_ms;

	while (!config->stop)
	{
		usleep(UINTERVAL);
		i = 0;
		while (i < config->n)
		{
			ph = &config->philosophers[i];
			gettimeofday(&now, NULL);
			delta_ms = (now.tv_sec - ph->last_meal_start_time.tv_sec) * 1000
				+ (now.tv_usec - ph->last_meal_start_time.tv_usec) / 1000;
			if (delta_ms > config->time_to_die)
				death_notify(ph);
			++i;
		}
	}
}

static inline void	philosopher_think(t_ph *me)
{
	state_notify(me, "is thinking");
}

static inline void	philosopher_sleep(t_ph *me)
{
	state_notify(me, "is sleeping");
	msleep(me, me->config->time_to_sleep);
}

static inline void	change_handedness(int *one_fork, int *another_fork)
{
	int	tmp;

	tmp = *one_fork;
	*one_fork = *another_fork;
	*another_fork = tmp;
}

void	*philosopher(void *arg)
{
	t_ph	*me;
	int		one_fork;
	int		another_fork;

	me = (t_ph *)arg;
	one_fork = me->i;
	another_fork = (me->i + 1) % me->config->n;
	if (me->i % 2 == 1)
		change_handedness(&one_fork, &another_fork);
	while (!me->config->stop)
	{
		philosopher_think(me);
		philosopher_eat(me, one_fork, another_fork);
		philosopher_sleep(me);
	}
	return (NULL);
}
