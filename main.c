/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/06 14:57:01 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->vars->death_m);
	philo->starve = get_time() + philo->vars->t_die;
	pthread_mutex_unlock(&philo->vars->death_m);
	display_state(philo, "is eating");
	usleep(philo->vars->t_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->right);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		if (death_check(philo->vars) || fed_check(philo->vars))
			return (NULL);
		display_state(philo, "is thinking");
		philo_eat(philo);
		if (philo->n_eat != -1)
		{
			pthread_mutex_lock(&philo->vars->fed_m);
			philo->n_eat--;
			if (philo->n_eat == 0)
				philo->vars->n_fed--;
			pthread_mutex_unlock(&philo->vars->fed_m);
		}
		display_state(philo, "is sleeping");
		usleep(philo->vars->t_sleep * 1000);
	}
	return (NULL);
}

void	death_watcher(t_vars *vars)
{
	int	i;

	i = 0;
	while (1 && !fed_check(vars))
	{
		pthread_mutex_lock(&vars->death_m);
		if (vars->philos[i].starve <= get_time())
		{
			vars->death = 1;
			pthread_mutex_unlock(&vars->death_m);
			pthread_mutex_lock(&vars->display);
			printf("%lld %d %s\n", get_time() - vars->starttime,
				vars->philos[i].id + 1, "died");
			pthread_mutex_unlock(&vars->display);
			return ;
		}
		pthread_mutex_unlock(&vars->death_m);
		if (i++ <= vars->number)
			i = 0;
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		i;

	parse_vars(ac, av, &vars);
	pthread_mutex_init(&vars.fed_m, NULL);
	pthread_mutex_init(&vars.display, NULL);
	pthread_mutex_init(&vars.death_m, NULL);
	init_philo(&vars, vars.philos);
	death_watcher(&vars);
	if (vars.number == 1)
		pthread_mutex_unlock(&vars.philos[0].right);
	i = -1;
	while (++i < vars.number)
		pthread_join(vars.philos[i].philo_t, NULL);
	i = -1;
	while (++i < vars.number)
		pthread_mutex_destroy(&vars.philos[i].right);
	pthread_mutex_destroy(&vars.display);
	pthread_mutex_destroy(&vars.death_m);
	pthread_mutex_destroy(&vars.fed_m);
	return (0);
}
