/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/21 19:27:15 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

struct		s_vars;

typedef struct s_philo
{
	int				id;
	long long		starve;
	int				n_eat;
	pthread_t		philo_t;
	pthread_mutex_t	*left;
	pthread_mutex_t	right;
	struct s_vars	*vars;
}					t_philo;

typedef struct s_vars
{
	int				number;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				n_fed;
	long long		starttime;
	t_philo			philos[256];
	pthread_mutex_t	display;
	pthread_mutex_t	death_m;
	pthread_mutex_t	fed_m;
	int				death;
}					t_vars;

void				display_state(t_philo *philo, char *statemsg);
void				ft_error(char *errmsg);
void				parse_vars(int ac, char **av, t_vars *vars);
void				init_philo(t_vars *vars, t_philo *philos);
void				*routine(void *p);
long long			get_time(void);
int					fed_check(t_vars *vars);
int					death_check(t_vars *vars);

char				*ft_itoa(int n);
int					ft_atoi(const char *nptr);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);

#endif