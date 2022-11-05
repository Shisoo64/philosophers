/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/05 23:30:55 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void parse(int ac, char **av, t_vars vars)
{
    if (ac < 5 || ac > 6)
        ft_error("Wrong argument number.");
    vars.number = ft_atoi(av[2]);
    vars.t_die = ft_atoi(av[3]);
    vars.t_eat = ft_atoi(av[4]);
    vars.t_sleep = ft_atoi(av[5]);
    vars.philo_list = malloc(sizeof(t_philo) * vars.number);
    if (ac == 6)
        vars.n_eat = ft_atoi(av[6]);
    else
        vars.n_eat = 0;
    if(!CHECK DES VARS)
        ft_error("Wrong argument.");
}

void ft_error(char *errmsg)
{
    ft_putendl_fd(errmsg, 2);
    exit(1);
}

void display_state(int num, char *statemsg)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    int timestamp = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    ft_putstr_fd(ft_itoa(timestamp), 1);
    ft_putchar_fd(' ', 1);
    ft_putstr_fd(ft_itoa(num), 1);
    ft_putendl_fd(statemsg, 1);
}
