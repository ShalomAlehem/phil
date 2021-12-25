/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_notify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:48:33 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 00:51:05 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
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

void	state_notify(t_ph *ph, const char *msg)
{
	long int	time_delta;

	sem_wait(ph->config->notification);
	if (!ph->config->is_simulation_finished)
	{
		time_delta = get_time_delta(&ph->config->start_time);
		print(time_delta, ph->i + 1, msg);
	}
	sem_post(ph->config->notification);
}

void	death_notify(t_ph *ph)
{
	long int	time_delta;

	sem_wait(ph->config->notification);
	if (!ph->config->is_simulation_finished)
	{
		time_delta = get_time_delta(&ph->config->start_time);
		print(time_delta, ph->i + 1, "died");
		sem_post(ph->config->death_or_meals_event);
		ph->config->is_simulation_finished = TRUE;
	}
	else
		sem_post(ph->config->notification);
}

void	debug_print(t_ph *ph, const char *msg)
{
	long int	time_delta;

	sem_wait(ph->config->notification);
	time_delta = get_time_delta(&ph->config->start_time);
	print(time_delta, ph->i + 1, msg);
	sem_post(ph->config->notification);
}

void	debug_print0(t_config *config, const char *msg)
{
	long int	time_delta;

	sem_wait(config->notification);
	time_delta = get_time_delta(&config->start_time);
	print(time_delta, 0, msg);
	sem_post(config->notification);
}
