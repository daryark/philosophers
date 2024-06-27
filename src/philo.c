/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/27 16:58:34 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	printf("Thread worked\n");
	//*close lock
	ph->meals_ate += 1;
	sleep(3);
	printf("End of thread, %d\n", ph->meals_ate);
	//*open lock
    return ((void *)philo);
}

bool	create_threads_run(t_philosophers *data)
{
	int	i;

	i = -1;
	if (!create_forks(&data->fork_arr, data->n_philos))
		return (false);
	init_philos(data);
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->philo_arr[i].thread, NULL, &philo_routine, &data->philo_arr[i]))
			return (clean_philo_arr(&data->philo_arr), false);
	}
	printf("threads done\n");
	clean_mtx_arr(&data->fork_arr);
	printf("mtx cleaned\n");
	clean_philo_arr(&data->philo_arr);
	printf("cleaned prog\n");
	return (true);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	
	if (err_check(ac, av))
		return (1);
	if (!init_prog(av, &data))
		return (printf("Program init failed\n"));
	//*start dinner
	//!print some data that is ready(created) just to see how the process is going on!!
	if (!create_threads_run(&data))
		return (printf("Program run failed"));
	return (0);
}
//pthread_create(&philo.thread, NULL, &routine, &philo);