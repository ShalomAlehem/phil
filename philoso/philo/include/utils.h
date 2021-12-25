/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:38:36 by rmander           #+#    #+#             */
/*   Updated: 2021/10/08 22:10:12 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include <sys/time.h>

# define TRUE	1
# define FALSE	0

# define EXIT_OK	0
# define EXIT_ERROR	1

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define SH_COLOR_WHITE		"\033[37m"
# define SH_COLOR_BLUE		"\033[34m"
# define SH_COLOR_RED		"\033[31m"
# define SH_COLOR_YELLOW	"\033[33m"
# define SH_COLOR_GREEN		"\033[32m"
# define SH_COLOR_RESET		"\033[m"

int			ft_isspace(int c);
int			ft_isdigit(int c);
ssize_t		ft_atoss(const char *str);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(const char *s, int fd);
time_t		to_msec(struct timeval *time);
int			alloca_to(void **ptr, size_t size);
void		ft_usleep(useconds_t usec);
useconds_t	to_usec(struct timeval *time);

#endif
