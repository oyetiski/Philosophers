/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:56:14 by olyetisk          #+#    #+#             */
/*   Updated: 2024/09/04 13:56:15 by olyetisk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# define ALIVE 1
# define DEAD 0

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				pn;
	int				status;
	int				eat_count;
	int				last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_hold	*hold;
	pthread_t		thread;
}	t_philosopher;

typedef struct s_hold
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				eat_count;
	int				dead_check;
	long			start_time;
	struct timeval	time_val;
	pthread_mutex_t	eat_mutex;
	t_philosopher	*philosopher;
	pthread_mutex_t	*fork;
}	t_hold;

void	*version(void *p);
void	placing(t_hold *hold, int ac, char **av);
void	ft_sleep(t_philosopher *p, long time);
void	p_check(t_philosopher *p);
void	my_printf(t_philosopher *philosopher, char	*msg);
long	time_milisecond(t_hold	*hold);
int		ft_atoi(const char *str);
int		ft_isnum(int c);
int		ft_arg_check(char **av);
int		my_exit(t_hold *hold);
void	to_do(t_philosopher *philo);
int		check_status(t_hold *hold, int i);
int		philo_make(t_hold *hold, int i);
int		p_control(t_hold *hold);
int		check_and_unlock(t_philosopher *philo, int mean);

#endif
