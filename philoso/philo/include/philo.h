/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:20:44 by rmander           #+#    #+#             */
/*   Updated: 2021/10/09 19:33:02 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <sys/time.h>

typedef enum e_state {
	STATE_FORK = 0,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_DIED
}	t_state;

typedef struct s_input
{
	unsigned int	n_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			times_to_eat;
}	t_input;

typedef struct s_fork
{
	unsigned int	n;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	unsigned int	n;
	t_fork			*l;
	t_fork			*r;
	time_t			start_ts;
	pthread_t		t;
	void			*data;
	pthread_mutex_t	lock;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher	*philosophers;
	t_fork			*forks;
	t_input			input;
	time_t			start_ts;
	unsigned int	alive;
	pthread_mutex_t	*lock;
	unsigned int	n_philo_fed;
	pthread_mutex_t	*fedlock;
}	t_data;

void	init(t_data *data);
int		parse(int argc, char **argv, t_input *input);
int		setup(t_data *data);
void	print(t_data *data, t_philosopher *p, t_state state);

#endif
