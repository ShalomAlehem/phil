/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 03:54:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 03:56:48 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <sys/wait.h>

#include "philosophers.h"

void	wait_for_threads_and_processes(t_config *cfg)
{
	int	i;

	cfg->is_simulation_finished = TRUE;
	i = -1;
	while (++i < cfg->n)
	{
		sem_post(cfg->philosophers[i].simulation_finished);
		sem_wait(cfg->simulation_finished_ack);
		sem_post(cfg->philosophers[i].started_eating);
		sem_post(cfg->philosophers[i].others_satiated);
	}
	sem_post(cfg->notification);
	while (i-- > 0)
		if (cfg->philosophers[i].pid)
			(void)waitpid(cfg->philosophers[i].pid, NULL, 0);
	if (cfg->satiety_controller)
		pthread_join(cfg->satiety_controller, NULL);
}

void	wait_for_threads(t_config *config)
{
	if (config->death_monitor)
		pthread_join(config->death_monitor, NULL);
	if (config->sim_end_monitor)
		pthread_join(config->sim_end_monitor, NULL);
}
