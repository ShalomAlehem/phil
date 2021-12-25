/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 00:39:48 by rmander           #+#    #+#             */
/*   Updated: 2021/10/08 22:14:13 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

static	void	forks(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->input.n_philo)
		pthread_mutex_destroy(&data->forks[i++].mutex);
	free(data->forks);
	data->forks = NULL;
}

static	void	cleanmutex(pthread_mutex_t	**mutex)
{
	pthread_mutex_destroy(*mutex);
	free(*mutex);
	*mutex = NULL;
}

static void	philosophers(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->input.n_philo)
		pthread_mutex_destroy(&data->philosophers[i++].lock);
	free(data->philosophers);
	data->philosophers = NULL;
}

void	clean(void *memory)
{
	t_data	*data;

	data = NULL;
	if (memory)
	{
		data = (t_data *)memory;
		if (data->lock)
			cleanmutex(&data->lock);
		if (data->fedlock)
			cleanmutex(&data->fedlock);
		if (data->forks)
			forks(data);
		if (data->philosophers)
			philosophers(data);
	}
}
