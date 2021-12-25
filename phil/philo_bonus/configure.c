/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:41:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 00:23:25 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "philosophers.h"

static int	configure_times(t_config *config, int argc, char **argv)
{
	int	i;
	int	params[5];

	i = 0;
	memset(params, 0, sizeof(params));
	while (++i < MAX_COMMANDLINE_ARGS)
	{
		if (i < MIN_COMMANDLINE_ARGS || argc == MAX_COMMANDLINE_ARGS)
		{
			if (get_number(argv[i], &params[i - 1]) == FAIL)
				return (FAIL);
		}
		else
			params[i - 1] = -1;
	}
	config->n = params[0];
	config->time_to_die = params[1];
	config->time_to_eat = params[2];
	config->time_to_sleep = params[3];
	config->min_n_meals = params[4];
	gettimeofday(&config->start_time, NULL);
	return (SUCCESS);
}

static int	configure_philosophers(t_config *config)
{
	int		i;
	t_ph	*ph;

	config->philosophers = malloc(sizeof(t_ph) * config->n);
	if (config->philosophers == NULL)
		return (FAIL);
	memset(config->philosophers, 0, sizeof(t_ph) * config->n);
	i = config->n;
	while (i-- > 0)
	{
		ph = &config->philosophers[i];
		ph->config = config;
		ph->i = i;
		ph->last_meal_start_time = config->start_time;
		ph->semname_se = get_semname(SEMNAME_STARTED_EATING, i);
		ph->semname_os = get_semname(SEMNAME_OTHERS_SATIATED, i);
		ph->semname_sf = get_semname(SEMNAME_SIM_FINISHED, i);
		if (ph->semname_se == NULL || ph->semname_os == NULL
			|| ph->semname_sf == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	open_semaphore(const char *semname, sem_t **sem,
	unsigned int value)
{
	(void)sem_unlink(semname);
	*sem = sem_open(semname, O_CREAT | O_EXCL, 0770, value);
	if (*sem == SEM_FAILED)
		return (FAIL);
	return (SUCCESS);
}

static int	open_semaphores(t_config *config)
{
	unsigned int	i;
	t_ph			*ph;

	if (open_semaphore(SEMNAME_DEATH_OR_MEALS,
			&config->death_or_meals_event, 0u) == FAIL)
		return (FAIL);
	i = (unsigned int)config->n;
	if (open_semaphore(SEMNAME_FORKS, &config->forks, i) == FAIL)
		return (FAIL);
	if (open_semaphore(SEMNAME_NOTIFICATION, &config->notification, 1u) == FAIL)
		return (FAIL);
	if (open_semaphore(
			SEMNAME_SIM_FIN_ACK, &config->simulation_finished_ack, 0) == FAIL)
		return (FAIL);
	while (i-- > 0)
	{
		ph = &config->philosophers[i];
		if (open_semaphore(ph->semname_se, &ph->started_eating, 0u) == FAIL)
			return (FAIL);
		if (open_semaphore(ph->semname_os, &ph->others_satiated, 1u) == FAIL)
			return (FAIL);
		if (open_semaphore(ph->semname_sf, &ph->simulation_finished, 0) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

t_config	*configure(int argc, char **argv)
{
	t_config	*config;

	if (argc < 5 || argc > 6)
		return (free_retnull(ERRMSG_ARG_NUM, NOTHING_TO_FREE));
	config = malloc(sizeof(t_config));
	if (config == NULL)
		return (free_retnull(ERRMSG_MALLOC_FAIL, NOTHING_TO_FREE));
	memset(config, 0, sizeof(t_config));
	if (configure_times(config, argc, argv) == FAIL)
		return (free_retnull(NO_ERRMSG, &config));
	if (configure_philosophers(config) == FAIL)
		return (free_retnull(ERRMSG_MALLOC_FAIL, &config));
	if (open_semaphores(config) == FAIL)
		return (free_retnull("Can't open semaphore", &config));
	config->is_config_inited = TRUE;
	return (config);
}
