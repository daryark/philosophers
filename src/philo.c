/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/01 18:39:28 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *ph)
{
	t_philo *philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 1)
		ft_usleep(philo->data->eat_time);
	printf("Thread worked\n");
	print_state((gettimeofday_in_mcrsec() - philo->data->prog_start_time) / 1000, philo->id + 1, THINK);
	//*close lock
	philo->meals_ate += 1;
	sleep(3);
	printf("End of thread, %d\n", philo->meals_ate);
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
		{
			printf(RED "clean return\n"  RE);
			return (clean_philo_arr(&data->philo_arr), false);
		}
		printf(GREEN "PHILO\nphilo->id: %d\nphilo->r_fork: %p (right philo fork)\nphilo->l_fork: %p (own fork)\nphilo->thread: %lu\n, philo->meals_ate: %d\n, philo->ate_last_time: %ld\n" RE, data->philo_arr[i].id, data->philo_arr[i].r_fork, data->philo_arr[i].l_fork, data->philo_arr[i].thread, data->philo_arr[i].meals_ate, data->philo_arr[i].ate_last_time);
	}
	printf("threads done\n");
	clean_mtx_arr(&data->fork_arr);
	clean_philo_arr(&data->philo_arr);
	printf("cleaned prog\n");
	return (true);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	//*enum arr or struct
	
	if (err_check(ac, av))
		return (1);
	if (!init_prog(av, &data))
		return (printf("Program init failed\n"));
	//*start dinner
	//!print some data that is ready(created) just to see how the process is going on!!
	printf(YELLOW "DATA\ndata->n_philos: %d\ndata->die_time: %ld\ndata->sleep_time: %ld\ndata->eat_time: %ld\ndata->n_meals: %d\ndata->has_died:%d\ndata->fork_arr: %p\ndata->philo_arr: %p\n" RE, data.n_philos, data.die_time, data.sleep_time, data.eat_time, data.n_meals, data.has_died, data.philo_arr, data.fork_arr);
	if (!create_threads_run(&data))
		return (printf("Program run failed"));
	return (0);
}
//pthread_create(&philo.thread, NULL, &routine, &philo);