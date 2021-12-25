/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 06:51:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/08 03:54:05 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
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

# define WAIT_ANY_CHILD			-1

# define NOTHING_TO_FREE		NULL
# define NO_ERRMSG				NULL
# define ERRMSG_ARG_GT_INTMAX	"Arguments must be numbers less than INT_MAX"
# define ERRMSG_ARG_LTE_ZERO	"Arguments must be positive numbers"
# define ERRMSG_ARG_NUM			"There must be from 4 to 5 arguments"
# define ERRMSG_MALLOC_FAIL		"Memory allocation failed"
# define ERRMSG_MIN_MEALS	"Minimal number of meals must be greater than zero"
# define ERRMSG_PTH_SC		"Can't create pthread for satiety controller"
# define ERRMSG_PTH_DM		"Can't create pthread for death monitor"
# define ERRMSG_PTH_SEM		"Can't create pthread for simulation end monitor"
# define ERR_PREFIX		"Error: "

# define SEMNAME_DEATH_OR_MEALS		"/death"
# define SEMNAME_FORKS				"/forks"
# define SEMNAME_NOTIFICATION		"/notify"
# define SEMNAME_STARTED_EATING		"/se"
# define SEMNAME_OTHERS_SATIATED	"/os"
# define SEMNAME_SIM_FINISHED		"/sf"
# define SEMNAME_SIM_FIN_ACK		"/sim_fin_ack"

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
	pthread_t		satiety_controller;
	pthread_t		death_monitor;
	pthread_t		sim_end_monitor;
	struct timeval	start_time;
	t_ph			*philosophers;
	sem_t			*death_or_meals_event;
	sem_t			*simulation_finished_ack;
	sem_t			*forks;
	sem_t			*notification;
	t_bool			is_config_inited;
	t_bool			is_simulation_finished;
	t_bool			is_child_process;
}	t_config;

struct	s_philosopher
{
	int				i;
	pid_t			pid;
	struct timeval	last_meal_start_time;
	sem_t			*started_eating;
	char			*semname_se;
	sem_t			*others_satiated;
	char			*semname_os;
	sem_t			*simulation_finished;
	char			*semname_sf;
	t_config		*config;
};

void		clean_up(t_config **config);
t_config	*configure(int argc, char **argv);
void		*control_satiety(void *config);
void		death_notify(t_ph *philosopher);
void		debug_print(t_ph *philosopher, const char *msg);
void		debug_print0(t_config *config, const char *msg);
size_t		ft_strlen(const char *str);
ssize_t		ft_write(int fd, const void *buf, size_t size);
int			free_retint(const int ret, const char *err_msg, t_config **config);
void		*free_retnull(const char *err_msg, t_config **config);
int			get_number(const char *str, int *number);
char		*get_semname(const char *prefix, int i);
long		get_time_delta(struct timeval *start_time);
void		*monitor_death(void *arg);
void		msleep(t_ph *philosopher, int ms);
void		philosopher(t_config **config, int i);
void		philosopher_eat(t_ph *philosopher);
void		print_number(int fd, long long int n);
void		state_notify(t_ph *philosopher, const char *msg);
void		wait_for_threads(t_config *config);
void		wait_for_threads_and_processes(t_config *config);

#endif
