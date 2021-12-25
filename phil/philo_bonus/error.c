/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:44:04 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 01:09:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stddef.h>
#include <unistd.h>

#include "philosophers.h"

static inline void	print_error(const char *err_msg, t_config **config)
{
	int	i;

	if (config != NULL && *config != NULL && (*config)->is_config_inited)
	{
		sem_post((*config)->death_or_meals_event);
		i = (*config)->n;
		while (i-- > 0)
		{
			sem_post((*config)->simulation_finished_ack);
			sem_post((*config)->philosophers[i].simulation_finished);
			sem_post((*config)->philosophers[i].started_eating);
			sem_post((*config)->philosophers[i].others_satiated);
		}
	}
	ft_write(STDERR, ERR_PREFIX, ft_strlen(ERR_PREFIX));
	ft_write(STDERR, err_msg, ft_strlen(err_msg));
	write(STDERR, "\n", 1);
}

static inline void	print_error_and_clean_config(
	const char *err_msg, t_config **config)
{
	if (err_msg != NULL)
		print_error(err_msg, config);
	if (config != NULL)
		clean_up(config);
}

int	free_retint(const int ret, const char *err_msg, t_config **config)
{
	print_error_and_clean_config(err_msg, config);
	return (ret);
}

void	*free_retnull(const char *err_msg, t_config **config)
{
	print_error_and_clean_config(err_msg, config);
	return (NULL);
}
