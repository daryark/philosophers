/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:02:12 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/27 16:56:08 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	create_forks(t_fork **arr, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(&((*arr)[i].mtx), NULL))
			return (clean_mtx_arr(arr), false);
		(*arr)[i].taken = false;
	}
	return (true);
}

void	init_philos(t_philosophers *data)
{
	int	i;
	t_philo *arr;

	arr = data->philo_arr;
	i = -1;
	while (++i < data->n_philos)
	{
		arr[i].r_fork = &data->fork_arr[i % data->n_philos];
		arr[i].l_fork = NULL;
		if (data->n_philos != 1)
			arr[i].l_fork = &data->fork_arr[i - 1 % data->n_philos];
		arr[i].id = i;
		arr[i].meals_ate = 0;
		arr[i].ate_last_time = gettimeofday_in_mcrsec();
		//data of all prog: //*arr[n]->data = data ??
	}
}

bool init_prog(char **av, t_philosophers *data)
{
	data->n_philos = (int)ft_atol(av[1]);
	data->die_time = ft_atol(av[2]);
	data->sleep_time = ft_atol(av[3]);
	data->eat_time = ft_atol(av[4]);
	data->n_meals = -1;
	if (av[5])
		data->n_meals = (int)ft_atol(av[5]);
	data->philo_arr = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo_arr)
		return (false);
	data->fork_arr = malloc(sizeof(t_fork) * data->n_philos);
	if (!data->fork_arr)
		return (free(data->philo_arr), false);
	printf("prog inited\n");
	return (true);
}