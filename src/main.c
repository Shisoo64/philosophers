/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/05 23:31:11 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_eat(int num, t_vars vars)
{
    if (!vars.philo_list[num - 1].iseating && vars.philo_list[num - 1].right && !vars.philo_list[num].left)
    {
        vars.philo_list[num - 1].right = 0;
        vars.philo_list[num].left = 1;
    }
    if (!vars.philo_list[num + 1].iseating && vars.philo_list[num + 1].left && !vars.philo_list[num].right)
    {
        vars.philo_list[num + 1].left = 0;
        vars.philo_list[num].right = 1;
    }
    if (!vars.philo_list[num].right || !vars.philo_list[num].left)
        return (1);
    display_state(num, " is eating");
    vars.philo_list[num].iseating = 1;
    usleep(vars.t_eat);
    vars.philo_list[num].iseating = 0;
    vars.philo_list[num].starve = TIMESTAMP_MS;
    return (0);
}

void philo_sleep(int num, t_vars vars)
{
    display_state(num, " is sleeping");
    vars.philo_list[num].issleeping = 1;
    usleep(vars.t_sleep);
    vars.philo_list[num].issleeping = 0;
    display_state(num, " is thinking");
}

void routine(int num)
{
    if (vars.philo_list[num].starve == TIMESTAMP_MS + vars.t_die)
        ft_error("A PHILOSOPHER IS DEAD");
    if (vars.philo_list[num].iseating || vars.philo_list[num].issleeping)
        return ;
    if (!philo_eat(num))
        return ;
    philo_sleep();
}

int	main(int ac, char **av)
{
    t_vars vars;
    pthread_t *philos;
    int i;

    parse(ac, av, vars);
    philos = malloc(sizeof(pthread_t) * vars.number);
    i = -1;
    while (++i < vars.number)
        if (pthread_create(&philos[i], NULL, routine, i))
            ft_error("Thread error.");
    free(vars.philo_list);
    free(philos);
}
