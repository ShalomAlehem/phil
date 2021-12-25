/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 02:33:33 by rmander           #+#    #+#             */
/*   Updated: 2021/10/08 00:25:59 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <sys/time.h>

/*
* @brief Custom usleep function.
*
* Works only above 25 microseconds.
*
* @param usec Number of microseconds to sleep for.
*/
void	ft_usleep(useconds_t usec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&now, NULL);
	start = now;
	while ((to_usec(&now) - to_usec(&start)) < usec)
	{
		usleep(25);
		gettimeofday(&now, NULL);
	}
}
