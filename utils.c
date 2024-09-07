/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:56:19 by olyetisk          #+#    #+#             */
/*   Updated: 2024/09/07 15:19:08 by olyetisk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		res = str[i] - '0' + res * 10;
		i++;
	}
	return (res * sign);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	ft_arg_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (ft_isnum(av[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	placing(t_hold *hold, int ac, char **av)
{
	int	i;

	i = 1;
	hold->num_of_philo = ft_atoi(av[i++]);
	hold->time_to_die = ft_atoi(av[i++]);
	hold->time_to_eat = ft_atoi(av[i++]);
	hold->time_to_sleep = ft_atoi(av[i++]);
	if (ac == 6)
		hold->num_must_eat = ft_atoi(av[i]);
	else
		hold->num_must_eat = -1;
}

void	*version(void *p)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p;//void * gelmek zorunda
	if (philo->hold->num_of_philo == 1) //toplam filozofun sayısı 1 ise 
	{
		ft_sleep(philo, philo->hold->time_to_die);//kaç ms yemezse ölücek time to die
		p_check(philo);
		usleep(2000);//burdan sonra devam etmesin diye
	}
	if (philo->pn % 2 == 0)
		usleep(750);
	to_do(philo);
	return (NULL);
}
