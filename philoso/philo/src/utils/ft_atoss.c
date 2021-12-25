/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:29:27 by rmander           #+#    #+#             */
/*   Updated: 2021/10/02 22:54:24 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static ssize_t	ft_pow(ssize_t n, ssize_t power)
{
	ssize_t	res;

	res = 1;
	while (power--)
		res *= n;
	return (res);
}

static ssize_t	ft_negate(ssize_t value, int neg)
{
	if (neg)
		value *= (-1);
	return (value);
}

ssize_t	ft_atoss(const char *str)
{
	ssize_t		result;
	const char	*end;
	ssize_t		count;
	ssize_t		i;
	int			neg;

	while (ft_isspace(*str))
		str++;
	neg = (*str == '-');
	result = 0;
	count = 0;
	i = 0;
	if (neg || (*str == '+'))
		str++;
	end = str;
	while (*end && ft_isdigit(*end))
	{
		count++;
		end++;
	}
	end--;
	while (i < count)
		result += (*end-- - '0') * ft_pow(10, i++);
	return (ft_negate(result, neg));
}
