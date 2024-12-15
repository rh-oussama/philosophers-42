/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:19:31 by oussama           #+#    #+#             */
/*   Updated: 2024/07/03 12:51:06 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_init_helper(t_mutex **mutex, int *i, t_mutex *tmp2)
{
	if (*i > 0)
	{
		tmp2->next = (*mutex);
		(*mutex)->prev = tmp2;
	}
	fill_left_fork(mutex, (*mutex)->param->philo_number);
}

t_mutex	*create_mutex_node(int philo_id, t_philo *param)
{
	t_mutex	*node;

	node = malloc(sizeof(t_mutex));
	if (!node)
		return (NULL);
	init_node(node, philo_id, param);
	if (!node->r_forks)
	{
		free(node);
		return (NULL);
	}
	pthread_mutex_init(&node->eat_sc_lock, NULL);
	if (pthread_mutex_init(node->r_forks, NULL) != 0)
	{
		free(node->r_forks);
		free(node);
		return (NULL);
	}
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	fork_init(t_mutex **mutex, t_philo *param)
{
	int		i;
	t_mutex	*tmp;
	t_mutex	*tmp2;

	i = 0;
	tmp2 = NULL;
	while (i < param->philo_number)
	{
		tmp = create_mutex_node(i + 1, param);
		if (!tmp)
			return ;
		if (i == 0)
			*mutex = tmp;
		else
		{
			tmp2->next = tmp;
			tmp->prev = tmp2;
		}
		tmp2 = tmp;
		i++;
	}
	fork_init_helper(mutex, &i, tmp2);
}

void	fill_left_fork(t_mutex **mutex, int philo_count)
{
	t_mutex	*tmp;
	int		i;

	i = 0;
	tmp = *mutex;
	while (i < philo_count)
	{
		tmp->l_forks = tmp->prev->r_forks;
		tmp = tmp->next;
		i++;
	}
}

void	philo_init(char **argv, t_philo *param, t_mutex **info)
{
	param->check_neat = 0;
	param->philo_number = ft_atol(argv[1]);
	param->t_die = ft_atol(argv[2]);
	param->t_eat = ft_atol(argv[3]);
	param->t_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		param->check_neat = 1;
		param->n_eat = ft_atol(argv[5]);
	}
	if (param->philo_number == 0 || (param->check_neat && param->n_eat == 0))
	{
		printf("Error\n");
		return ;
	}
	param->philo_start = get_time();
	pthread_mutex_init(&(param->status), NULL);
	param->d_staus = 0;
	fork_init(info, param);
}
