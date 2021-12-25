/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:48:21 by rmander           #+#    #+#             */
/*   Updated: 2021/10/09 19:32:32 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "clean.h"
#include <stdlib.h>

int	pexit(const char *message, void *data, int status)
{
	if (data)
		clean(data);
	if (message)
		ft_putstr_fd(message, STDERR);
	return (status);
}
