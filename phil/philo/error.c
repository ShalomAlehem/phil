/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:44:04 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/01 11:41:36 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

#include "philosophers.h"

static inline void	eprint(const char *err_msg)
{
	ft_write(STDERR, ERR_PREFIX, ft_strlen(ERR_PREFIX));
	ft_write(STDERR, err_msg, ft_strlen(err_msg));
	write(STDERR, "\n", 1);
}

static inline void	print_error(const char *err_msg, t_config **config)
{
	if (config != NULL && *config != NULL && (*config)->are_mutexes_inited)
	{
		pthread_mutex_lock(&(*config)->notification_mutex);
		(*config)->stop = TRUE;
		eprint(err_msg);
		pthread_mutex_unlock(&(*config)->notification_mutex);
	}
	else
		eprint(err_msg);
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
