/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:02:12 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/03 19:04:28 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(t_philo *philo, mtx_t *f1, mtx_t *f2)
{
	philo->fork1 = f1;
	philo->fork2 = f2;
}

void	init_philos(t_philosophers *data)
{
	int	i;
	t_philo *arr;
	mtx_t	*cur;
	mtx_t	*next;

	arr = data->philo_arr;
	i = -1;
	while (++i < data->n_philos)
	{
		cur = &data->fork_arr[i % data->n_philos];
		next = &data->fork_arr[(i + 1) % data->n_philos];
		if (data->n_philos - i == 1)
			assign_forks(&arr[i], next, cur);
		else
			assign_forks(&arr[i], cur, next);
		if (data->n_philos == 1)
			arr[i].fork2 = NULL;
		arr[i].id = i + 1;
		arr[i].meals_ate = 0;
		arr[i].is_full = false;
		arr[i].ate_last_time = gettimeofday_in_mcs();
		arr[i].data = data;
	}
}

bool init_prog(char **av, t_philosophers *data)
{
	data->n_philos = (int)ft_atol(av[1]);
	data->die_time = ft_atol(av[2]) * 1000;
	data->eat_time = ft_atol(av[3]) * 1000;
	data->sleep_time = ft_atol(av[4]) * 1000;
	data->is_dead = false;
	data->full_philos = 0;
	data->n_meals = -1;
	if (av[5])
		data->n_meals = (int)ft_atol(av[5]);
	data->philo_arr = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo_arr)
		return (false);
	data->fork_arr = malloc(sizeof(mtx_t) * data->n_philos);
	if (!data->fork_arr)
		return (free(data->philo_arr), false);
	data->prog_start_time = gettimeofday_in_mcs();
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&data->check_mtx, NULL))
		return (false);
	return (true);
}
