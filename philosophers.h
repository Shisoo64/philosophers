/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/07 16:45:38 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int		iseating;
	int		issleeping;
	int		starve;
	int		left;
	int		right;
}			t_philo;

typedef struct s_vars
{
	int		id;
	int		number;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
	t_philo	*philo_list;
}			t_vars;

void		display_state(int num, char *statemsg);
void		ft_error(char *errmsg);
void		parse(int ac, char **av, t_vars vars);
int			get_time(void);

char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);

#endif