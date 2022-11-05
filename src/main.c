/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/05 22:57:25 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void ft_error(char *errmsg)
{
    ft_putendl_fd(errmsg, 2);
    exit(1);
}

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

void eat(int num, t_vars vars)
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
        return ;
    display_state(num, " is eating");
    vars.philo_list[num].iseating = 1;
    usleep(vars.t_eat);
    vars.philo_list[num].iseating = 0;
}

void sleep(int num, t_vars vars)
{
    display_state(num, " is sleeping");
    vars.philo_list[num].issleeping = 1;
    usleep(vars.t_sleep);
    vars.philo_list[num].issleeping = 0;
}

void routine(int num)
{
    eat(num);
    sleep();
    think();
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
