/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/08 18:01:40 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&philo->right);
	display_state(philo, " is eating");
	philo->iseating = 1;
	usleep(philo->vars->t_eat);
	philo->iseating = 0;
	philo->starve = get_time() + philo->vars->t_eat;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->right);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	display_state(philo, " is sleeping");
	philo->issleeping = 1;
	usleep(philo->vars->t_sleep);
	philo->issleeping = 0;
	display_state(philo, " is thinking");
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->starve != get_time())
	{
		if (!philo->issleeping && !philo->iseating)
		{
			if (philo_eat(philo))
				philo_sleep(philo);
		}
	}
	display_state(philo, " died");
	exit(0);
}

void	init_philo(t_vars *vars, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i <= vars->number)
	{
		pthread_mutex_init(&philos[i].right, NULL);





		philos[i].left = &philos[i - 1].right;




		philos[i].vars = vars;
		if (pthread_create(&philos[i].philo_t, NULL, &routine,
				&philos[i]) == 1)
			ft_error("Thread error.");
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		i;

	parse_vars(ac, av, &vars);
	init_philo(&vars, vars.philos);
	pthread_mutex_init(&vars.mutex, NULL);
	i = -1;
	while (++i <= vars.number)
		pthread_join(vars.philos[i].philo_t, NULL);
	pthread_mutex_destroy(&vars.mutex);
}
