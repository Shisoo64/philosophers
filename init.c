/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:35:07 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/05 19:10:06 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_vars(t_vars *vars)
{
	if (vars->number < 1 || vars->number > 256)
		return (1);
	if (vars->t_die < 1 || vars->t_eat < 1 || vars->t_sleep < 1)
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
	vars->death = 0;
	vars->n_fed = vars->number;
	vars->n_eat = -1;
	if (ac == 6)
		vars->n_eat = ft_atoi(av[5]);
	if (check_vars(vars))
		ft_error("Wrong argument.");
}

void	init_philo(t_vars *vars, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < vars->number)
	{
		pthread_mutex_init(&philos[i].right, NULL);
		if (i != 0)
			philos[i].left = &philos[i - 1].right;
		philos[i].vars = vars;
		philos[i].starve = get_time() + vars->t_die;
		philos[i].id = i;
		philos[i].n_eat = vars->n_eat;
	}
	if (vars->number == 1)
		philos[0].left = &philos[0].right;
	else
		philos[0].left = &philos[i - 1].right;
	i = -1;
	while (++i < vars->number)
		if (pthread_create(&philos[i].philo_t, NULL, &routine,
				&philos[i]) != 0)
			ft_error("Thread error.");
}
