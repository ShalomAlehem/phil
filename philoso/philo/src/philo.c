/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:20:23 by rmander           #+#    #+#             */
/*   Updated: 2021/10/09 19:31:42 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"
#include "utils.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

int	parse(int argc, char **argv, t_input *input)
{
	char	*str;
	int		i;
	char	**strs;

	str = NULL;
	strs = argv;
	i = 0;
	while (i < argc)
	{
		str = *strs;
		while (*str)
			if (!ft_isdigit(*str++))
				return (FALSE);
		++strs;
		++i;
	}
	input->n_philo = ft_atoss(argv[0]);
	if (input->n_philo == 0)
		return (FALSE);
	input->time_to_die = ft_atoss(argv[1]);
	input->time_to_eat = ft_atoss(argv[2]);
	input->time_to_sleep = ft_atoss(argv[3]);
	if (argc > 4)
		input->times_to_eat = ft_atoss(argv[4]);
	return (TRUE);
}

void	init(t_data *data)
{
	data->input = (t_input){.n_philo = 0, .time_to_eat = 0, .time_to_die = 0,
		.time_to_sleep = 0, .times_to_eat = -1};
	data->start_ts = 0;
	data->forks = NULL;
	data->philosophers = NULL;
	data->alive = TRUE;
	data->lock = NULL;
	data->fedlock = NULL;
	data->n_philo_fed = 0;
}

void	print(t_data *data, t_philosopher *p, t_state state)
{
	struct timeval	time;
	const char		*colors[] = {SH_COLOR_WHITE, SH_COLOR_GREEN,
								SH_COLOR_BLUE, SH_COLOR_YELLOW, SH_COLOR_RED};
	const char		*messages[] = {"has taken a fork", "is eating",
								"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(data->lock);
	gettimeofday(&time, NULL);
	if (data->alive || state == STATE_DIED)
		printf("%s%lu %u %s%s\n", colors[state],
			to_msec(&time) - data->start_ts, p->n,
			messages[state], SH_COLOR_RESET);
	pthread_mutex_unlock(data->lock);
}

static int	plant(t_data *data)
{
	unsigned int	i;
	unsigned int	l;
	unsigned int	r;
	struct timeval	time;

	if (!alloca_to((void **)&data->philosophers,
			data->input.n_philo * sizeof(t_philosopher)))
		return (FALSE);
	i = 0;
	l = 0;
	r = 1;
	gettimeofday(&time, NULL);
	while (i < data->input.n_philo)
	{
		data->philosophers[i].n = i + 1;
		data->philosophers[i].l = &data->forks[l];
		data->philosophers[i].r = &data->forks[r % data->input.n_philo];
		data->philosophers[i].start_ts = to_msec(&time);
		data->philosophers[i].data = (void *)data;
		pthread_mutex_init(&data->philosophers[i].lock, NULL);
		l = r;
		r = r + 1;
		++i;
	}
	return (TRUE);
}

int	setup(t_data *data)
{
	unsigned int	i;

	if (!alloca_to((void **)&data->forks, data->input.n_philo * sizeof(t_fork)))
		return (FALSE);
	i = 0;
	while (i < data->input.n_philo)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i].n = i + 1;
		++i;
	}
	if (!plant(data))
		return (FALSE);
	if (!alloca_to((void **)&data->lock, sizeof(pthread_mutex_t)))
		return (FALSE);
	pthread_mutex_init(data->lock, NULL);
	if (!alloca_to((void **)&data->fedlock, sizeof(pthread_mutex_t)))
		return (FALSE);
	pthread_mutex_init(data->fedlock, NULL);
	return (TRUE);
}
