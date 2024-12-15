/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:15:49 by orhaddao          #+#    #+#             */
/*   Updated: 2024/07/04 16:01:42 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <threads.h>
# include <unistd.h> 

typedef struct s_philo
{
	pthread_mutex_t	status;
	int				philo_number;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	long int		n_eat;
	int				d_staus;
	int				check_neat;
	long int		philo_start;

}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*l_forks;
	pthread_mutex_t	*r_forks;
	pthread_mutex_t	eat_sc_lock;
	t_philo			*param;
	int				philo_id;
	long int		eat_start;
	int				eat_count;
	int				checked;
	struct s_mutex	*next;
	struct s_mutex	*prev;
}					t_mutex;

long int			ft_atol(const char *nptr);
void				philo_init(char **argv, t_philo *param, t_mutex **info);
int					check_args(int argc, char **argv, t_philo *param,
						t_mutex **info);
long int			get_time(void);
t_mutex				*create_mutex_node(int philo_id, t_philo *param);
void				fork_init(t_mutex **mutex, t_philo *param);
void				fill_left_fork(t_mutex **mutex, int philo_count);
void				monitoring(t_mutex *info);
void				print_message(char *str, t_mutex *info);
int					ft_usleep(size_t milliseconds, t_mutex *tmp);
void				busy_wait_loop(int wait);
void				*routine(void *pa);
void				start_philo(pthread_t *philo_th, t_philo *param,
						t_mutex *info);
int					take_fork_order(t_mutex *info);
void				philo_eat(t_mutex *info);
void				destroy_all(t_philo *param, pthread_t *philo_th,
						t_mutex *info);
void				init_node(t_mutex *node, int philo_id, t_philo *param);

#endif