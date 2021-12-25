/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_usec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 00:16:08 by rmander           #+#    #+#             */
/*   Updated: 2021/10/08 22:10:34 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>

useconds_t	to_usec(struct timeval *time)
{
	return ((useconds_t)(time->tv_sec * 1000000) + time->tv_usec);
}
