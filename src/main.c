/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/03 19:44:13 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_forks(mtx_t **arr, int n)
{
	int i;

	i = -1;
	while (++i < n)
		pthread_mutex_init(&((*arr)[i]), NULL);
}

void	create_threads(t_philosophers *data)
{
	int	i;

	i = -1;
	init_philos(data);
	pthread_mutex_lock(&data->print_mtx);
	while (++i < data->n_philos)
		pthread_create(&data->philo_arr[i].thread, NULL, &philo_routine, &data->philo_arr[i]);
	pthread_mutex_unlock(&data->print_mtx);
}

void	*philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		monitor_usleep(ph->data->eat_time, ph);
	while (1)
	{
		if( !philo_eat(ph))
			break ;
		if (!philo_sleep(ph))
			break ;
		if (!monitor_usleep(1, ph))
			break ;
		print_state(ph, THINK);
		if (check_full(ph->data) || check_dead(ph))
			break ;
	}
    return (NULL);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	
	if (err_check(ac, av))
		return (1);
	if (!init_prog(av, &data))
		return (printf("Program init failed\n"));
	create_forks(&data.fork_arr, data.n_philos);
	create_threads(&data);
	stop_prog(&data);
	return (0);
}
