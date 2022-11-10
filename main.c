/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/10 18:18:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	display_state(philo, " has taken a fork");
	pthread_mutex_lock(&philo->right);
	display_state(philo, " has taken a fork");
	display_state(philo, " is eating");
	philo->iseating = 1;
	usleep(philo->vars->t_eat * 1000);
	philo->iseating = 0;
	philo->starve = get_time() + philo->vars->t_eat;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->right);
}

void	philo_sleep(t_philo *philo)
{
	display_state(philo, " is sleeping");
	philo->issleeping = 1;
	usleep(philo->vars->t_sleep * 1000);
	philo->issleeping = 0;
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->starve <= get_time())
	{
		if (!philo->issleeping && !philo->iseating)
		{
			display_state(philo, " is thinking");
			philo_eat(philo);
			if (philo->starve >= get_time())
				break ;
			philo_sleep(philo);
		}
	}
	display_state(philo, " died");
	return (NULL);
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
		philos[i].starve = 0;
		philos[i].id = i;
	}
	philos[0].left = &philos[i].right;
	while (i-- != 0)
		if (pthread_create(&philos[i].philo_t, NULL, &routine,
				&philos[i]) == 1)
			ft_error("Thread error.");
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		i;

	parse_vars(ac, av, &vars);
	pthread_mutex_init(&vars.display, NULL);
	init_philo(&vars, vars.philos);
	i = -1;
	while (++i <= vars.number)
	{
		pthread_join(vars.philos[i].philo_t, NULL);
		pthread_mutex_destroy(&vars.philos[i].right);
	}
	pthread_mutex_destroy(&vars.display);
}
