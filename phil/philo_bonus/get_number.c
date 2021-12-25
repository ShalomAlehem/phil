/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:44:53 by dpowdere          #+#    #+#             */
/*   Updated: 2021/09/30 22:56:08 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

#include "philosophers.h"

int	get_number(const char *str, int *number)
{
	int	n;
	int	m;

	n = 0;
	m = -1;
	while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v')
		++str;
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		m = n * 10 + (*str++ - '0');
		if (m < n)
			return (free_retint(FAIL, ERRMSG_ARG_GT_INTMAX, NOTHING_TO_FREE));
		n = m;
	}
	if (*str != '\0' || n < 1)
		return (free_retint(FAIL, ERRMSG_ARG_LTE_ZERO, NOTHING_TO_FREE));
	*number = n;
	return (SUCCESS);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		++len;
	return (len);
}

void	print_number(int fd, long long int n)
{
	int				sign;
	long long int	power10;
	long long int	x;
	char			c;

	if (n < 0)
		write(fd, "-", 1);
	sign = 1;
	if (n < 0)
		sign = -1;
	power10 = 1;
	x = n / 10;
	while (x != 0)
	{
		x /= 10;
		power10 *= 10;
	}
	while (power10 != 0)
	{
		x = n / power10;
		c = (unsigned char)('0' + x * sign);
		n %= power10;
		power10 /= 10;
		write(fd, &c, 1);
	}
}

/*
** An iterative equivalent of the `write` system call, returning
** the value of the last call, if an error occurs, and the total
** number of bytes written if every call to `write` is successful.
*/

ssize_t	ft_write(int fd, const void *buf, size_t size)
{
	ssize_t	total_size;
	ssize_t	partial_size;

	total_size = 0;
	partial_size = write(fd, buf, size);
	while (partial_size >= 0 && (size_t)partial_size < size)
	{
		total_size += partial_size;
		buf = (unsigned char *)buf + partial_size;
		size -= partial_size;
		partial_size = write(fd, buf, size);
	}
	if (partial_size < 0)
		return (partial_size);
	total_size += partial_size;
	return (total_size);
}
