/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_notify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:48:33 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/01 11:50:03 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>

#include "philosophers.h"

static inline void	print(long int time_delta, int ph_id, const char *msg)
{
	print_number(STDOUT, (long long int)time_delta);
	write(STDOUT, " ", 1);
	print_number(STDOUT, (long long int)ph_id);
	write(STDOUT, " ", 1);
	ft_write(STDOUT, msg, ft_strlen(msg));
	write(STDOUT, "\n", 1);
}

void	state_notify(t_ph *philosopher, const char *msg)
{
	long int	time_delta;

	pthread_mutex_lock(&philosopher->config->notification_mutex);
	if (!philosopher->config->stop)
	{
		time_delta = get_time_delta(&philosopher->config->start_time);
		print(time_delta, philosopher->i + 1, msg);
	}
	pthread_mutex_unlock(&philosopher->config->notification_mutex);
}

void	death_notify(t_ph *philosopher)
{
	long int	time_delta;

	pthread_mutex_lock(&philosopher->config->notification_mutex);
	if (!philosopher->config->stop)
	{
		time_delta = get_time_delta(&philosopher->config->start_time);
		print(time_delta, philosopher->i + 1, "died");
		philosopher->config->stop = TRUE;
	}
	pthread_mutex_unlock(&philosopher->config->notification_mutex);
}
