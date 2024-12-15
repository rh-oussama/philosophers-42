/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:19:31 by oussama           #+#    #+#             */
/*   Updated: 2024/06/04 00:01:39 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_mutex *info)
{
	pthread_mutex_lock(&(info->param->status));
	if (info->param->d_staus == 0)
		printf("%ld\t%d %s\n", get_time() - info->param->philo_start,
			info->philo_id, str);
	pthread_mutex_unlock(&(info->param->status));
}

int	ft_usleep(size_t milliseconds, t_mutex *tmp)
{
	size_t	start;
	int		i;

	i = 0;
	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		usleep(500);
		if (i == 4)
		{
			i = 0;
			pthread_mutex_lock(&(tmp->param->status));
			if (tmp->param->d_staus)
			{
				pthread_mutex_unlock(&(tmp->param->status));
				break ;
			}
			pthread_mutex_unlock(&(tmp->param->status));
		}
		i++;
	}
	return (0);
}

void	busy_wait_loop(int wait)
{
	int	i;

	i = 0;
	while (i < wait)
	{
		usleep(50);
		i++;
	}
}

void	destroy_all(t_philo *param, pthread_t *philo_th, t_mutex *info)
{
	int		i;
	t_mutex	*tmp;
	t_mutex	*tmp2;

	i = 0;
	tmp = info;
	while (i < param->philo_number)
	{
		pthread_join(philo_th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(param->status));
	free(philo_th);
	i = 0;
	while (i < param->philo_number)
	{
		pthread_mutex_destroy(tmp->r_forks);
		free(tmp->r_forks);
		pthread_mutex_destroy(&tmp->eat_sc_lock);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		i++;
	}
}

void	init_node(t_mutex *node, int philo_id, t_philo *param)
{
	node->eat_count = 0;
	node->eat_start = get_time();
	node->philo_id = philo_id;
	node->param = param;
	node->checked = 0;
	node->r_forks = malloc(sizeof(pthread_mutex_t));
}
