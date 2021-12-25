/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mon.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:14:18 by rmander           #+#    #+#             */
/*   Updated: 2021/10/09 16:40:16 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <pthread.h>
#include <sys/time.h>

static unsigned int	fed(t_data *data)
{
	unsigned int	flag;

	flag = FALSE;
	pthread_mutex_lock(data->fedlock);
	flag = (data->n_philo_fed == data->input.n_philo);
	pthread_mutex_unlock(data->fedlock);
	return (flag);
}

void	killer(t_data *data, unsigned int i)
{
	pthread_mutex_lock(data->lock);
	data->alive = FALSE;
	pthread_mutex_unlock(data->lock);
	print(data, &data->philosophers[i], STATE_DIED);
}

unsigned int	lifecheck(t_data *data, unsigned int i)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((to_msec(&time) - data->philosophers[i].start_ts)
		>= data->input.time_to_die);
}

void	monitor(t_data *data)
{
	unsigned int		i;
	unsigned int		died;
	const unsigned int	limited = data->input.times_to_eat > 0;

	while (TRUE)
	{
		i = 0;
		while (i < data->input.n_philo)
		{
			pthread_mutex_lock(&data->philosophers[i].lock);
			died = lifecheck(data, i);
			if (died || (limited && fed(data)))
			{
				if (died)
					killer(data, i);
				pthread_mutex_unlock(&data->philosophers[i].lock);
				break ;
			}
			pthread_mutex_unlock(&data->philosophers[i].lock);
			++i;
		}
		if (died || (limited && fed(data)))
			break ;
		ft_usleep(500);
	}
}
