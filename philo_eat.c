/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:19:31 by oussama           #+#    #+#             */
/*   Updated: 2024/06/03 23:57:04 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork_order(t_mutex *info)
{
	if (info->philo_id % 2 == 0)
	{
		pthread_mutex_lock(info->r_forks);
		print_message("has taken a fork", info);
		pthread_mutex_lock(info->l_forks);
	}
	else
	{
		if (info->eat_count == 0)
			busy_wait_loop(5);
		pthread_mutex_lock(info->l_forks);
		print_message("has taken a fork", info);
		if (info->r_forks == info->l_forks)
		{
			ft_usleep(info->param->t_die * 2, info);
			return (0);
		}
		pthread_mutex_lock(info->r_forks);
	}
	print_message("has taken a fork", info);
	return (1);
}

void	philo_eat(t_mutex *info)
{
	pthread_mutex_unlock(&(info->param->status));
	print_message("is thinking", info);
	busy_wait_loop(3);
	if (!take_fork_order(info))
	{
		pthread_mutex_unlock(info->l_forks);
		return ;
	}
	pthread_mutex_lock(&(info->eat_sc_lock));
	info->eat_start = get_time();
	pthread_mutex_unlock(&(info->eat_sc_lock));
	print_message("is eating", info);
	pthread_mutex_lock(&(info->eat_sc_lock));
	info->eat_count++;
	pthread_mutex_unlock(&(info->eat_sc_lock));
	ft_usleep(info->param->t_eat, info);
	pthread_mutex_unlock(info->l_forks);
	pthread_mutex_unlock(info->r_forks);
	print_message("is sleeping", info);
	ft_usleep(info->param->t_sleep, info);
	busy_wait_loop(3);
}

void	*routine(void *pa)
{
	t_mutex	*info;

	info = (t_mutex *)pa;
	while (1)
	{
		pthread_mutex_lock(&(info->param->status));
		if (!info->param->d_staus)
			philo_eat(info);
		else
		{
			pthread_mutex_unlock(&(info->param->status));
			break ;
		}
	}
	return (NULL);
}
