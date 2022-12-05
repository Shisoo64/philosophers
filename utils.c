/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/05 15:57:05 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(char *errmsg)
{
	ft_putendl_fd(errmsg, 2);
	exit(1);
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
