/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:56:32 by olyetisk          #+#    #+#             */
/*   Updated: 2024/09/04 13:56:32 by olyetisk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	dead_check(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->hold->eat_mutex);
	if (philo->hold->dead_check == DEAD)
	{
		pthread_mutex_unlock(&philo->hold->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->hold->eat_mutex);
	return (0);
}

int	check_and_unlock(t_philosopher *philo, int mean)
{
	if (dead_check(philo))
	{
		if (mean == 0)
			return (0);
		pthread_mutex_unlock(philo->r_fork);
		if (mean == 2)
			pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	return (1);
}

int	check_eat_count(t_hold *hold, int i)
{
	i = -1;
	pthread_mutex_lock(&hold->eat_mutex);
	while (hold->num_must_eat != -1 && ++i < hold->num_of_philo)
		if (hold->philosopher[i].eat_count < hold->num_must_eat)
			break ;
	if (hold->num_must_eat != -1 && i == hold->num_of_philo)
	{
		hold->dead_check = 0;
		pthread_mutex_unlock(&hold->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&hold->eat_mutex);
	return (1);
}

int	check_status(t_hold *hold, int i)
{
	while (++i < hold->num_of_philo)
	{
		p_check(&hold->philosopher[i]);
		pthread_mutex_lock(&hold->eat_mutex);
		if (hold->philosopher[i].status == DEAD)
		{
			hold->dead_check = 0;
			printf("%ld\t%d died\n", time_milisecond(hold),
				hold->philosopher[i].pn);
			pthread_mutex_unlock(&hold->eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&hold->eat_mutex);
	}
	if (check_eat_count(hold, -1) == 0)
		return (0);
	return (1);
}

int	p_control(t_hold *hold)
{
	int	c;

	c = 1;
	if (philo_make(hold, -1) == 0)
		c = my_exit(hold);
	while (c)
		if (check_status(hold, -1) == 0)//main thread burda süürekli çalışıyor ölen var mı diye geri kalanlar yemek vb verison threadde yapılıyor 
			c = my_exit(hold);
	return (c);
}
