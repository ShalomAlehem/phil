/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 07:00:25 by dpowdere          #+#    #+#             */
/*   Updated: 2021/09/30 22:35:24 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "philosophers.h"

int	configure_times(t_config *config, int argc, char **argv)
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
	config->hungry_philosophers = config->n;
	gettimeofday(&config->start_time, NULL);
	return (SUCCESS);
}

int	init_mutexes(t_config *config)
{
	int	i;

	if (pthread_mutex_init(&config->notification_mutex, NULL))
		return (FAIL);
	if (pthread_mutex_init(&config->hungry_count_mutex, NULL))
		return (FAIL);
	i = 0;
	while (i < config->n)
	{
		if (pthread_mutex_init(&config->forks[i], NULL))
			return (FAIL);
		++i;
	}
	config->are_mutexes_inited = TRUE;
	return (SUCCESS);
}

int	configure_philosophers(t_config *config)
{
	int	i;

	config->threads = malloc(sizeof(pthread_t) * config->n);
	if (config->threads == NULL)
		return (FAIL);
	memset(config->threads, 0, sizeof(pthread_t) * config->n);
	config->philosophers = malloc(sizeof(t_ph) * config->n);
	if (config->philosophers == NULL)
		return (FAIL);
	memset(config->philosophers, 0, sizeof(t_ph) * config->n);
	i = config->n;
	while (i-- > 0)
	{
		config->philosophers[i].i = i;
		config->philosophers[i].must_wait_for_others = FALSE;
		config->philosophers[i].last_meal_start_time = config->start_time;
		config->philosophers[i].config = config;
	}
	config->forks = malloc(sizeof(pthread_mutex_t) * config->n);
	if (config->forks == NULL)
		return (FAIL);
	memset(config->forks, 0, sizeof(pthread_mutex_t) * config->n);
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
	if (init_mutexes(config) == FAIL)
		return (free_retnull("Can't create mutex", &config));
	return (config);
}

int	main(int argc, char **argv)
{
	int			i;
	t_config	*config;

	config = configure(argc, argv);
	if (config == NULL)
		return (FAIL);
	i = 0;
	while (i < config->n)
	{
		if (pthread_create(&config->threads[i], NULL,
				philosopher, &config->philosophers[i]) != 0)
			return (free_retint(FAIL, "Can't create pthread", &config));
		++i;
	}
	monitor_death(config);
	while (i-- > 0)
		(void)pthread_join(config->threads[i], NULL);
	clean_up(&config);
	return (SUCCESS);
}
