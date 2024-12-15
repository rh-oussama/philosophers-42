/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:14:02 by oussama           #+#    #+#             */
/*   Updated: 2024/07/03 13:10:16 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_number(char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long int	ft_atol(const char *nptr)
{
	long int	numb;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	numb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		numb = numb * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * numb);
}

void	print_error_message(void)
{
	printf("Usage: ./philo <arg-1> <arg-2> <arg-3> <arg-4> [arg-5]\n");
	printf(" -> arg-1: number_of_philosophers\n");
	printf(" -> arg-2: time_to_die\n");
	printf(" -> arg-3: time_to_eat\n");
	printf(" -> arg-4: time_to_sleep\n");
	printf(" -> arg-5 (optional): \
number_of_times_each_philosopher_must_eat\n");
}

int	check_args(int argc, char **argv, t_philo *param, t_mutex **info)
{
	char	**tmp;

	tmp = argv;
	if (argc != 5 && argc != 6)
	{
		print_error_message();
		return (0);
	}
	argv++;
	while (*argv)
	{
		if (!check_is_number(*argv) || ft_atol(*argv) < 0)
		{
			printf("Invalid Arguments!\n");
			return (0);
		}
		argv++;
	}
	philo_init(tmp, param, info);
	if (param->philo_number == 0 || (param->check_neat && !param->n_eat))
		return (0);
	return (1);
}
