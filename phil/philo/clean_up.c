/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 21:26:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/09/30 16:16:47 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>

#include "philosophers.h"

static void	clean_pthread_data(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->n)
	{
		config->philosophers[i].config = NULL;
		++i;
	}
	free(config->philosophers);
	config->philosophers = NULL;
}

static void	clean_mutex(pthread_mutex_t *mutex)
{
	if (mutex == NULL || *(int *)mutex == (int)PTHREAD_MUTEX_DEFAULT)
		return ;
	pthread_mutex_destroy(mutex);
}

static void	clean_forks(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->n)
	{
		clean_mutex(&config->forks[i]);
		++i;
	}
	free(config->forks);
	config->forks = NULL;
}

void	clean_up(t_config **p_config)
{
	t_config	*config;

	config = *p_config;
	if (p_config != NULL && config != NULL)
	{
		if (config->threads != NULL)
		{
			free(config->threads);
			config->threads = NULL;
		}
		if (config->philosophers != NULL)
			clean_pthread_data(config);
		if (config->forks != NULL)
			clean_forks(config);
		clean_mutex(&config->notification_mutex);
		clean_mutex(&config->hungry_count_mutex);
		free(config);
		*p_config = NULL;
	}
}
