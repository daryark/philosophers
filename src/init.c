/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:02:12 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 04:20:16 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//*if 1 ONLY philo, both forks will be id = 1, id = 1
static void	assign_forks(t_philo *philo, int f1, int f2)
{
	philo->fork1_id = f1;
	philo->fork2_id = f2;
}

void	run_prog(t_philosophers *data, int n_meals)
{
	int	i;

	create_forks(data->forks, data->n_philos);
	pthread_mutex_init(&data->check_dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].meals_left = n_meals;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		if (i == data->n_philos - 1)
			assign_forks(&data->philos[i], 1, data->n_philos);
		else
			assign_forks(&data->philos[i], (i + 2), (i + 1));
	// philo->first_fork = &forks[(philo_position + 1) % philo_nb];
	// philo->second_fork = &forks[philo_position];
	// if (philo->id % 2 == 0)
	// {
	// 	philo->first_fork = &forks[philo_position];
	// 	philo->second_fork = &forks[(philo_position + 1) % philo_nb];
	// }
		// assign_forks(&data->philos[i], 1, data->n_philos);
	// if (i == 0)
	// 	assign_forks(&data->philos[i], 1, 2);
	// else if (i == data->n_philos - 1)
	// 	assign_forks(&data->philos[i], data->n_philos, 1);
	// else if (i % 2 == 1)
	// 	assign_forks(&data->philos[i], i + 1, i + 2);
	// else
	// 	assign_forks(&data->philos[i], i + 2, i + 1);
	data->philos[i].ate_last_time = gettimeofday_in_mcs();
	}
	i = -1;
	pthread_mutex_lock(&data->print_lock);
	// pthread_mutex_lock(&data->check_dead_lock);
	// pthread_mutex_lock(&data->meal_lock);
	while (++i < data->n_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]);
	}
	data->prog_start_time = gettimeofday_in_mcs();
	pthread_create(&data->monitor, NULL, &monitor_routine, data);
	pthread_mutex_unlock(&data->print_lock);
	// pthread_mutex_unlock(&data->check_dead_lock);
	// pthread_mutex_unlock(&data->meal_lock);
}

bool prog(char **av, t_philosophers *data)
{	
	data->n_philos = ft_atol(av[1]);
	data->die_time = ft_atol(av[2]) * 1000;
	data->eat_time = ft_atol(av[3]) * 1000;
	data->sleep_time = ft_atol(av[4]) * 1000;
	data->stop_prog_flag = false;
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (false);
	data->forks = malloc(sizeof(t_fork) * data->n_philos);
	if (!data->forks)
		return (free(data->philos), false);
	if (av[5])
		run_prog(data, ft_atol(av[5]));
	else
		run_prog(data, -1);
	clean_prog(data);
	return (true);
}

//*decrease meals_left each time philo eats, if it is not -1