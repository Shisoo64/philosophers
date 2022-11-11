/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/11 15:28:25 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	display_state(philo, " has taken a fork");
	pthread_mutex_lock(&philo->right);
	pthread_mutex_lock(&philo->vars->starve_m);
	philo->starve = get_time() + philo->vars->t_die;
	pthread_mutex_unlock(&philo->vars->starve_m);
	display_state(philo, " has taken a fork");
	display_state(philo, " is eating");
	usleep(philo->vars->t_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->right);
}

void	philo_sleep(t_philo *philo)
{
	display_state(philo, " is sleeping");
	usleep(philo->vars->t_sleep * 1000);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!philo->vars->death)
	{
		display_state(philo, " is thinking");
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	death_watcher(t_vars *vars)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&vars->starve_m);
		if (vars->philos[i].starve <= get_time())
		{
			vars->death = 1;
			display_state(&vars->philos[i], " died");
			pthread_mutex_unlock(&vars->starve_m);
			return ;
		}
		pthread_mutex_unlock(&vars->starve_m);
		if (i++ <= vars->number)
			i = 0;
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		i;

	parse_vars(ac, av, &vars);
	pthread_mutex_init(&vars.display, NULL);
	pthread_mutex_init(&vars.starve_m, NULL);
	init_philo(&vars, vars.philos);
	death_watcher(&vars);
	exit (1);
	i = -1;
	while (++i <= vars.number)
	{
		pthread_join(vars.philos[i].philo_t, NULL);
		pthread_mutex_destroy(&vars.philos[i].right);
	}
	pthread_mutex_destroy(&vars.display);
	pthread_mutex_destroy(&vars.starve_m);
	return (0);
}
