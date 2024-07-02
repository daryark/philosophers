/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 16:09:09 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		monitor_usleep(ph->data->eat_time, ph);
	while (1)
	{
		if (ph->data->full_philos == ph->data->n_philos || check_dead(ph))
		{
			printf(YELLOW "return prev check\n" RE);
			break ;
		}
		if (!monitor_usleep(1, ph))
			break ;
		print_state(ph, THINK);
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
	// if (ph->data->is_dead)
	// 	print_state(ph, DIE);
	if (ph->data->full_philos)
		printf(GREEN "finished" RE);
	//*close lock
	// printf("End of thread, %d\n", ph->meals_ate);
	//*open lock
    return (NULL);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	
	if (err_check(ac, av))
		return (1);
	if (!init_prog(av, &data))
		return (printf("Program init failed\n"));
	// printf(YELLOW "DATA\ndata->n_philos: %d\ndata->die_time: %ld\ndata->sleep_time: %ld\ndata->eat_time: %ld\ndata->n_meals: %d\ndata->is_dead:%d\ndata->fork_arr: %p\ndata->philo_arr: %p\n" RE, data.n_philos, data.die_time, data.sleep_time, data.eat_time, data.n_meals, data.is_dead, data.philo_arr, data.fork_arr);
	if (!create_forks(&data.fork_arr, data.n_philos)
		|| !create_threads(&data))
		return (printf("Program run failed"));
	stop_prog(&data);
	return (0);
}
