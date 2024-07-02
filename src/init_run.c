/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:02:12 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 16:18:56 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	create_forks(mtx_t **arr, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(&((*arr)[i]), NULL))
		{
			printf(RED "clean return mtx\n" RE);
			return (clean_mtx_arr(arr), false);
		}
	}
	return (true);
}

bool	create_threads(t_philosophers *data)
{
	int	i;

	i = -1;
	init_philos(data);
	pthread_mutex_lock(&data->print_mtx);
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->philo_arr[i].thread, NULL, &philo_routine, &data->philo_arr[i]))
		{
			printf(RED "clean return\n"  RE);
			return (clean_philo_arr(&data->philo_arr), false);
		}
		// printf(GREEN "PHILO\nphilo->id: %d\nphilo->fork1: %p\nphilo->fork2: %p\nphilo->thread: %lu\n, philo->meals_ate: %d\n, philo->ate_last_time: %ld\n" RE, data->philo_arr[i].id, data->philo_arr[i].fork1, data->philo_arr[i].fork2, data->philo_arr[i].thread, data->philo_arr[i].meals_ate, data->philo_arr[i].ate_last_time);
	}
	printf("threads done\n");
	pthread_mutex_unlock(&data->print_mtx);
	return (true);
}

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
	{
		printf(RED "clean return print_mtx\n" RE);
		return (false);
	}
	return (true);
}
