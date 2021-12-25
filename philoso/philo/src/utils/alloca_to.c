/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloca_to.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 01:05:50 by rmander           #+#    #+#             */
/*   Updated: 2021/10/05 01:05:57 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

int	alloca_to(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (FALSE);
	return (TRUE);
}
