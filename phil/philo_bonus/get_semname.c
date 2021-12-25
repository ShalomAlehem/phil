/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_semname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 13:41:53 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/01 12:01:57 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "philosophers.h"

static inline size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0 && src && dst)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	while (src && src[i])
		++i;
	return (i);
}

static inline char	*alloc_str(const char *prefix, int n, int *power10)
{
	int		digits;
	size_t	size;
	char	*str;

	digits = 1;
	*power10 = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		*power10 *= 10;
		++digits;
	}
	size = ft_strlen(prefix) + digits + 1;
	str = malloc(size * sizeof(char));
	if (str == NULL)
		return (NULL);
	memset(str, 0, size * sizeof(char));
	return (str);
}

char	*get_semname(const char *prefix, int n)
{
	char	*sem_name;
	size_t	prefix_len;
	int		power10;
	int		i;

	sem_name = alloc_str(prefix, n, &power10);
	if (sem_name == NULL)
		return (NULL);
	prefix_len = ft_strlen(prefix);
	ft_strlcpy(sem_name, prefix, prefix_len + 1);
	i = 0;
	while (power10 != 0)
	{
		sem_name[prefix_len + i++] = (char)(n / power10 + '0');
		n %= power10;
		power10 /= 10;
	}
	sem_name[prefix_len + i] = '\0';
	return (sem_name);
}
