/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 00:58:36 by dpowdere          #+#    #+#             */
/*   Updated: 2021/09/30 11:46:32 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

#include "philosophers.h"

static inline void	remember_to_wait_for_others(t_ph *me)
{
	t_config *const	config = me->config;
	int				i;

	me->must_wait_for_others = TRUE;
	pthread_mutex_lock(&config->hungry_count_mutex);
	config->hungry_philosophers -= 1;
	if (config->hungry_philosophers == 0)
	{
		if (config->min_n_meals > 0)
			config->min_n_meals -= 1;
		if (config->min_n_meals == 0)
			config->stop = TRUE;
		i = 0;
		while (i < config->n)
		{
			if (config->philosophers[i].must_wait_for_others)
				config->philosophers[i].must_wait_for_others = FALSE;
			++i;
		}
		config->hungry_philosophers = config->n;
	}
	pthread_mutex_unlock(&config->hungry_count_mutex);
}

static inline void	take_forks(t_ph *me, int one_fork, int another_fork)
{
	if (me->config->n != 1)
	{
		pthread_mutex_lock(&me->config->forks[one_fork]);
		state_notify(me, "has taken a fork");
		pthread_mutex_lock(&me->config->forks[another_fork]);
		state_notify(me, "has taken a fork");
	}
	else
	{
		while (!me->config->stop)
			usleep(UINTERVAL);
	}
}

static inline void	put_forks(t_ph *me, int one_fork, int another_fork)
{
	if (me->config->n != 1)
	{
		pthread_mutex_unlock(&me->config->forks[one_fork]);
		pthread_mutex_unlock(&me->config->forks[another_fork]);
	}
}

void	philosopher_eat(t_ph *me, int one_fork, int another_fork)
{
	while (me->must_wait_for_others)
		usleep(me->i % UINTERVAL);
	take_forks(me, one_fork, another_fork);
	gettimeofday(&me->last_meal_start_time, NULL);
	state_notify(me, "is eating");
	remember_to_wait_for_others(me);
	msleep(me, me->config->time_to_eat);
	put_forks(me, one_fork, another_fork);
}
