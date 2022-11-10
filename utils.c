/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/10 17:56:52 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_vars(t_vars *vars)
{
	if (vars->number < 1)
		return (1);
	return (0);
}

void	parse_vars(int ac, char **av, t_vars *vars)
{
	if (ac < 5 || ac > 6)
		ft_error("Wrong argument number.");
	vars->number = ft_atoi(av[1]);
	vars->t_die = ft_atoi(av[2]);
	vars->t_eat = ft_atoi(av[3]);
	vars->t_sleep = ft_atoi(av[4]);
	vars->starttime = get_time();
	vars->n_eat = 0;
	if (ac == 6)
		vars->n_eat = ft_atoi(av[5]);
	if (check_vars(vars))
		ft_error("Wrong argument.");
}

void	ft_error(char *errmsg)
{
	ft_putendl_fd(errmsg, 2);
	exit(1);
}

int	get_time(void)
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
