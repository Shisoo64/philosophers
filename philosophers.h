/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/10 16:45:16 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct		s_vars;

typedef struct s_philo
{
	int				id;
	int				iseating;
	int				issleeping;
	int				starve;
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
	int				starttime;
	t_philo			philos[256];
	pthread_mutex_t	display;
}					t_vars;

void				display_state(t_philo *philo, char *statemsg);
void				ft_error(char *errmsg);
void				parse_vars(int ac, char **av, t_vars *vars);
int					get_time(void);

char				*ft_itoa(int n);
int					ft_atoi(const char *nptr);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);

#endif