/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/12 16:15:27 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(char *errmsg)
{
	ft_putendl_fd(errmsg, 2);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	display_state(t_philo *philo, char *statemsg)
{
	pthread_mutex_lock(&philo->vars->display);
	if (!death_check(philo->vars) && !fed_check(philo->vars))
	{
		printf("%lld %d %s\n", get_time() - philo->vars->starttime,
			philo->id + 1, statemsg);
	}
	pthread_mutex_unlock(&philo->vars->display);
}

int	death_check(t_vars *vars)
{
	int	val;

	pthread_mutex_lock(&vars->death_m);
	val = vars->death;
	pthread_mutex_unlock(&vars->death_m);
	return (val);
}

int	fed_check(t_vars *vars)
{
	int	val;

	pthread_mutex_lock(&vars->fed_m);
	val = 0;
	if (vars->n_fed == 0)
		val = 1;
	pthread_mutex_unlock(&vars->fed_m);
	return (val);
}
