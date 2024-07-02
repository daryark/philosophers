/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 21:08:32 by dyarkovs         ###   ########.fr       */
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
			return (clean_mtx_arr(arr, n), false);
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
			return (clean_philo_arr(&data->philo_arr, data->n_philos), false);
		}
		// printf(GREEN "PHILO\nphilo->id: %d\nphilo->fork1: %p\nphilo->fork2: %p\nphilo->thread: %lu\n, philo->meals_ate: %d\n, philo->ate_last_time: %ld\n" RE, data->philo_arr[i].id, data->philo_arr[i].fork1, data->philo_arr[i].fork2, data->philo_arr[i].thread, data->philo_arr[i].meals_ate, data->philo_arr[i].ate_last_time);
	}
	printf("threads done\n");
	pthread_mutex_unlock(&data->print_mtx);
	printf("print mtx unlocked\n");
	return (true);
}

void	*philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	printf("in philo %d routine\n", ph->id);
	if (ph->id % 2 == 0)
		monitor_usleep(ph->data->eat_time, ph);
	while (1)
	{
		// printf("check dead: %d\n", ph->data->is_dead);
		if (ph->data->full_philos == ph->data->n_philos || check_dead(ph))
		{
			printf(YELLOW "return prev check\n" RE);
			break ;
		}
		// printf("after check before think\n");
		if (!monitor_usleep(1, ph))
			break ;
		// printf("after check and think\n");
		print_state(ph, THINK);
		// printf("afther think print state\n");
		if (!philo_eat(ph) || ph->data->full_philos == ph->data->n_philos)
		{
			printf(YELLOW "return eat\n" RE);
			break ;
		}
		if (!philo_sleep(ph) || ph->data->full_philos == ph->data->n_philos)
		{
			printf(YELLOW "dead: %d, full: %d\n", ph->data->is_dead, ph->data->full_philos);
			printf(YELLOW "return sleep\n" RE);
			break ;
		}
	}
	printf("outside while(1) loop\n");
	printf("ph->data->full_philos: %d\n", ph->data->full_philos);
	if (ph->data->full_philos == ph->data->n_philos)
		printf(GREEN "finished" RE);
    return (NULL);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	
	if (err_check(ac, av))
		return (1);
	if (!init_prog(av, &data))
		return (printf("Program init failed\n"));
	if (!create_forks(&data.fork_arr, data.n_philos)
		|| !create_threads(&data))
		return (printf("Program run failed"));
	printf("returned from prog\n");
	stop_prog(&data);
	return (0);
}
