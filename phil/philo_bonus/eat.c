/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 00:58:36 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/07 23:26:39 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

#include "philosophers.h"

static inline void	take_forks(t_ph *me)
{
	sem_wait(me->config->forks);
	state_notify(me, "has taken a fork");
	if (me->config->n > 1)
	{
		sem_wait(me->config->forks);
		state_notify(me, "has taken a fork");
	}
	else
	{
		while (!me->config->is_simulation_finished)
			usleep(UINTERVAL);
	}
}

static inline void	eat(t_ph *me)
{
	gettimeofday(&me->last_meal_start_time, NULL);
	state_notify(me, "is eating");
	sem_post(me->started_eating);
	msleep(me, me->config->time_to_eat);
}

static inline void	put_forks(t_ph *me)
{
	sem_post(me->config->forks);
	sem_post(me->config->forks);
}

void	philosopher_eat(t_ph *me)
{
	sem_wait(me->others_satiated);
	take_forks(me);
	eat(me);
	put_forks(me);
}
