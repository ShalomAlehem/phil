/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:20:16 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/07 23:29:00 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

#include "philosophers.h"

long	get_time_delta(struct timeval *start_time)
{
	time_t			sec;
	suseconds_t		usec;
	struct timeval	now;

	gettimeofday(&now, NULL);
	sec = now.tv_sec - start_time->tv_sec;
	usec = now.tv_usec - start_time->tv_usec;
	return ((long)(sec * 1000 + usec / 1000));
}

void	msleep(t_ph *philosopher, int ms)
{
	long			delta_ms;
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, NULL);
	delta_ms = 0;
	while (delta_ms < ms && !philosopher->config->is_simulation_finished)
	{
		usleep(UINTERVAL);
		gettimeofday(&now, NULL);
		delta_ms = (now.tv_sec - start.tv_sec) * 1000
			+ (now.tv_usec - start.tv_usec) / 1000;
	}
}
