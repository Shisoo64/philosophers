/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/11 13:35:21 by rlaforge         ###   ########.fr       */
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
	ft_putstr_fd(ft_itoa(get_time() - philo->vars->starttime), 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(ft_itoa(philo->id + 1), 1);
	ft_putendl_fd(statemsg, 1);
	pthread_mutex_unlock(&philo->vars->display);
}
