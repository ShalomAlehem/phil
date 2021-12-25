/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:10:18 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/07 22:12:41 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <semaphore.h>
#include <unistd.h>

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int			i;
	t_config	*config;

	config = configure(argc, argv);
	if (config == NULL)
		return (FAIL);
	if (pthread_create(&config->satiety_controller, NULL,
			control_satiety, config) != 0)
		return (free_retint(FAIL, ERRMSG_PTH_SC, &config));
	i = -1;
	gettimeofday(&config->start_time, NULL);
	while (++i < config->n)
	{
		config->philosophers[i].pid = fork();
		if (config->philosophers[i].pid < 0)
			return (free_retint(FAIL, "Can't create process", &config));
		else if (config->philosophers[i].pid == 0)
			philosopher(&config, i);
	}
	(void)sem_wait(config->death_or_meals_event);
	clean_up(&config);
	return (SUCCESS);
}
