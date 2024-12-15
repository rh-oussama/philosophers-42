/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:19:31 by oussama           #+#    #+#             */
/*   Updated: 2024/07/03 13:32:06 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die_and_number_eat(t_mutex *tmp, int *n_eat)
{
	if ((get_time() - tmp->eat_start) > tmp->param->t_die)
	{
		tmp->param->d_staus = 1;
		printf("%ld\t%d died\n", get_time() - tmp->param->philo_start,
			tmp->philo_id);
		pthread_mutex_unlock(&tmp->eat_sc_lock);
		pthread_mutex_unlock(&(tmp->param->status));
		return (0);
	}
	if (!tmp->checked && tmp->eat_count >= tmp->param->n_eat
		&& tmp->param->check_neat)
	{
		(*n_eat)++;
		tmp->checked = 1;
	}
	if (tmp->param->check_neat && (*n_eat) == tmp->param->philo_number)
	{
		tmp->param->d_staus = 1;
		pthread_mutex_unlock(&tmp->eat_sc_lock);
		pthread_mutex_unlock(&(tmp->param->status));
		return (0);
	}
	return (1);
}

void	monitoring(t_mutex *info)
{
	int		n_eat;
	t_mutex	*tmp;

	n_eat = 0;
	tmp = info;
	while (1)
	{
		pthread_mutex_lock(&(tmp->param->status));
		pthread_mutex_lock(&tmp->eat_sc_lock);
		if (!check_die_and_number_eat(tmp, &n_eat))
			break ;
		pthread_mutex_unlock(&tmp->eat_sc_lock);
		pthread_mutex_unlock(&(tmp->param->status));
		usleep(50);
		tmp = tmp->next;
	}
}

void	start_philo(pthread_t *philo_th, t_philo *param, t_mutex *info)
{
	int		i;
	t_mutex	*tmp;

	i = 0;
	tmp = info;
	while (i < param->philo_number)
	{
		pthread_create(&(philo_th[tmp->philo_id - 1]), NULL, &routine,
			(void *)tmp);
		tmp = tmp->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo		param;
	pthread_t	*philo_th;
	t_mutex		*info;

	info = NULL;
	if (!check_args(argc, argv, &param, &info))
		return (1);
	philo_th = malloc(sizeof(pthread_t) * param.philo_number);
	start_philo(philo_th, &param, info);
	monitoring(info);
	destroy_all(&param, philo_th, info);
	return (0);
}
