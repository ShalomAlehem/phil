/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:32:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 00:17:21 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "philosophers.h"

void	*monitor_sim_end(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	sem_wait(ph->simulation_finished);
	ph->config->is_simulation_finished = TRUE;
	sem_post(ph->config->simulation_finished_ack);
	return (NULL);
}

void	*monitor_death(void *arg)
{
	long			delta_ms;
	struct timeval	now;
	t_ph			*ph;

	ph = (t_ph *)arg;
	while (!ph->config->is_simulation_finished)
	{
		usleep(UINTERVAL);
		gettimeofday(&now, NULL);
		delta_ms = (now.tv_sec - ph->last_meal_start_time.tv_sec) * 1000
			+ (now.tv_usec - ph->last_meal_start_time.tv_usec) / 1000;
		if (delta_ms > ph->config->time_to_die)
			death_notify(ph);
	}
	return (NULL);
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

void	philosopher(t_config **config, int i)
{
	t_ph		*me;
	t_config	*cfg;

	cfg = *config;
	cfg->is_child_process = TRUE;
	me = &cfg->philosophers[i];
	if (pthread_create(&cfg->sim_end_monitor, NULL, monitor_sim_end, me) != 0)
		exit(free_retint(FAIL, ERRMSG_PTH_SEM, config));
	if (pthread_create(&cfg->death_monitor, NULL, monitor_death, me) != 0)
		exit(free_retint(FAIL, ERRMSG_PTH_DM, config));
	while (!cfg->is_simulation_finished)
	{
		philosopher_think(me);
		philosopher_eat(me);
		philosopher_sleep(me);
	}
	exit(free_retint(SUCCESS, NO_ERRMSG, config));
}
