/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 01:18:39 by rmander           #+#    #+#             */
/*   Updated: 2021/10/09 19:40:31 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "mon.h"
#include "error.h"
#include "utils.h"
#include "clean.h"
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int	prepare(int argc, char *argv[], t_data *data)
{
	init(data);
	if (!parse(--argc, ++argv, &data->input))
	{
		ft_putstr_fd("Invalid arguments\n", STDERR);
		return (FALSE);
	}
	if (!setup(data))
		return (FALSE);
	return (TRUE);
}

void	eating(t_data *data, t_philosopher *p)
{
	struct timeval	time;	

	pthread_mutex_lock(&p->l->mutex);
	print(data, p, STATE_FORK);
	pthread_mutex_lock(&p->r->mutex);
	print(data, p, STATE_FORK);
	pthread_mutex_lock(&p->lock);
	gettimeofday(&time, NULL);
	p->start_ts = to_msec(&time);
	pthread_mutex_unlock(&p->lock);
	print(data, p, STATE_EATING);
	ft_usleep(data->input.time_to_eat * 1000);
	pthread_mutex_unlock(&p->r->mutex);
	pthread_mutex_unlock(&p->l->mutex);
}

void	*lifecycle(void *memory)
{
	t_data			*data;
	t_philosopher	*p;
	unsigned int	i;

	p = (t_philosopher *)memory;
	data = (t_data *)p->data;
	i = 0;
	while (data->alive)
	{
		eating(data, p);
		if ((data->input.times_to_eat > 0)
			&& (i == (data->input.times_to_eat - 1)))
		{
			pthread_mutex_lock(data->fedlock);
			++data->n_philo_fed;
			pthread_mutex_unlock(data->fedlock);
			break ;
		}
		print(data, p, STATE_SLEEPING);
		ft_usleep(data->input.time_to_sleep * 1000);
		print(data, p, STATE_THINKING);
		if (data->input.times_to_eat > 0)
			++i;
	}
	return (NULL);
}

void	run(t_data *data)
{
	struct timeval	time;
	unsigned int	i;
	unsigned int	count;

	gettimeofday(&time, NULL);
	data->start_ts = to_msec(&time);
	count = 0;
	while (count < 2)
	{
		i = 0;
		while (i < data->input.n_philo)
		{
			if (i % 2 == count)
			{
				pthread_create(&data->philosophers[i].t, NULL, lifecycle,
					(void *)&data->philosophers[i]);
				ft_usleep(500);
			}
			++i;
		}
		if (count++ == 0)
			ft_usleep(data->input.time_to_eat * 1000 * 0.95);
	}
}

int	main(int argc, char *argv[])
{
	t_data			data;
	unsigned int	i;

	if (argc < 5 || argc > 6)
		return (pexit("Invalid number of arguments\n", NULL, EXIT_ERROR));
	if (!prepare(argc, argv, &data))
		return (pexit(NULL, &data, EXIT_ERROR));
	if (data.input.times_to_eat == 0)
		return (pexit(NULL, &data, EXIT_OK));
	run(&data);
	monitor(&data);
	i = 0;
	while (i < data.input.n_philo)
		pthread_detach(data.philosophers[i++].t);
	clean(&data);
	return (EXIT_OK);
}
