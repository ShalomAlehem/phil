/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 06:51:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/01 11:48:58 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>
# include <sys/types.h>

# define MIN_COMMANDLINE_ARGS	5
# define MAX_COMMANDLINE_ARGS	6

# define STDOUT		1
# define STDERR		2

# define SUCCESS	0
# define FAIL		1

# define UINTERVAL	50

# define NOTHING_TO_FREE		NULL
# define NO_ERRMSG				NULL
# define ERRMSG_ARG_GT_INTMAX	"Arguments must be numbers less than INT_MAX"
# define ERRMSG_ARG_LTE_ZERO	"Arguments must be positive numbers"
# define ERRMSG_ARG_NUM			"There must be from 4 to 5 arguments"
# define ERRMSG_MALLOC_FAIL		"Memory allocation failed"
# define ERRMSG_MIN_MEALS	"Minimal number of meals must be greater than zero"
# define ERR_PREFIX		"Error: "

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philosopher	t_ph;
typedef struct s_config
{
	int				n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_n_meals;
	t_bool			stop;
	struct timeval	start_time;
	int				hungry_philosophers;
	pthread_t		*threads;
	t_ph			*philosophers;
	pthread_mutex_t	notification_mutex;
	pthread_mutex_t	hungry_count_mutex;
	pthread_mutex_t	*forks;
	t_bool			are_mutexes_inited;
}	t_config;

struct	s_philosopher
{
	int				i;
	t_bool			must_wait_for_others;
	struct timeval	last_meal_start_time;
	t_config		*config;
};

void	clean_up(t_config **config);
int		create_mutexes(t_config *config);
void	death_notify(t_ph *philosopher);
size_t	ft_strlen(const char *str);
ssize_t	ft_write(int fd, const void *buf, size_t size);
int		free_retint(const int ret, const char *err_msg, t_config **config);
void	*free_retnull(const char *err_msg, t_config **config);
int		get_number(const char *str, int *number);
long	get_time_delta(struct timeval *start_time);
void	monitor_death(t_config *config);
void	msleep(t_ph *philosopher, int ms);
void	*philosopher(void *philosopher);
void	philosopher_eat(t_ph *philosopher, int one_fork, int another_fork);
void	print_number(int fd, long long int n);
void	state_notify(t_ph *philosopher, const char *msg);

#endif
