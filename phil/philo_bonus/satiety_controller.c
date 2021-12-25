/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satiety_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:18:58 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/07 04:04:28 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stddef.h>

#include "philosophers.h"

void	*control_satiety(void *arg)
{
	t_config	*config;
	int			i;
	int			n_meals;

	config = (t_config *)arg;
	n_meals = 0;
	while (!config->is_simulation_finished)
	{
		i = config->n;
		while (i-- > 0)
			sem_wait(config->philosophers[i].started_eating);
		if (config->min_n_meals > 0)
		{
			++n_meals;
			if (n_meals >= config->min_n_meals)
			{
				sem_post(config->death_or_meals_event);
				break ;
			}
		}
		i = config->n;
		while (i-- > 0)
			sem_post(config->philosophers[i].others_satiated);
	}
	return (NULL);
}
