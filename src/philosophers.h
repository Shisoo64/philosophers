/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/05 22:49:33 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_philo
{
    int iseating;
    int issleeping;
    int state;
    int left;
    int right;
}               t_philo;

typedef struct s_vars
{
    int     number;
    int     t_die;
    int     t_eat;
    int     t_sleep;
    int     n_eat;
    t_philo *philo_list;
}               t_vars;

int	    ft_atoi(const char *nptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif