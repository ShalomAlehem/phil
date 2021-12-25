/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 21:26:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 03:55:56 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>

#include "philosophers.h"

static void	clean_philosophers(t_config *config)
{
	int		i;
	t_ph	*ph;

	i = 0;
	while (i < config->n)
	{
		ph = &config->philosophers[i++];
		free(ph->semname_se);
		ph->semname_se = NULL;
		free(ph->semname_os);
		ph->semname_os = NULL;
		free(ph->semname_sf);
		ph->semname_sf = NULL;
		ph->config = NULL;
	}
	free(config->philosophers);
	config->philosophers = NULL;
}

static void	clean_semaphore(const char *semname, sem_t *sem, t_bool in_child)
{
	if (sem == NULL || semname == NULL)
		return ;
	(void)sem_close(sem);
	if (!in_child)
		(void)sem_unlink(semname);
}

static void	clean_semaphores(t_config *config)
{
	int		i;
	t_ph	*ph;

	clean_semaphore(SEMNAME_DEATH_OR_MEALS, config->death_or_meals_event,
		config->is_child_process);
	clean_semaphore(SEMNAME_FORKS, config->forks, config->is_child_process);
	clean_semaphore(SEMNAME_NOTIFICATION, config->notification,
		config->is_child_process);
	if (config->philosophers == NULL)
		return ;
	i = 0;
	while (i < config->n)
	{
		ph = &config->philosophers[i++];
		clean_semaphore(ph->semname_se, ph->started_eating,
			config->is_child_process);
		clean_semaphore(ph->semname_os, ph->others_satiated,
			config->is_child_process);
		clean_semaphore(ph->semname_sf, ph->simulation_finished,
			config->is_child_process);
	}
}

void	clean_up(t_config **p_config)
{
	t_config	*config;

	config = *p_config;
	if (p_config != NULL && config != NULL)
	{
		if (config->is_config_inited)
		{
			if (config->is_child_process)
				wait_for_threads(config);
			else
				wait_for_threads_and_processes(config);
		}
		clean_semaphores(config);
		if (config->philosophers != NULL)
			clean_philosophers(config);
		free(config);
		*p_config = NULL;
	}
}
