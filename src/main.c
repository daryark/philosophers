/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 17:46:04 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Monitor philos while they run, until: (one is_dead) or all are full
void	*monitor_routine(void *data)
{
	t_philosophers *d;
	bool 			run;

	d = (t_philosophers *)data;
	run = true;
	while (run)
	{
		// pthread_mutex_lock(&d->print_lock);
		// printf("monitor ");
		// pthread_mutex_unlock(&d->print_lock);
		if (check_dead(d))
			run = false;
		if (check_full_all(d))
			run = false;
		ft_usleep(500);
	}
	return (data);
}

void	create_forks(t_fork *arr, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		arr[i].id = i + 1;
		pthread_mutex_init(&arr[i].fork, NULL);
	}
}

static void	think(t_philosophers *data)
{
	long	to_think;

	(void)data;
	// to_think = data->eat_time/2 - data->sleep_time;
	// if (to_think < 0)
	// 	to_think = 0;
	// if (data->n_philos % 2 == 0)
	// {
	// 	to_think = data->eat_time/2 - data->sleep_time;
	// 	if (to_think < 0)
	// 		to_think = 0;
	// }
	// else
	// 	to_think = 0;
	to_think = 1000;
	ft_usleep (to_think);
}

void	*philo_routine(void *philo)
{
	t_philo *p;
	bool	run;

	p = (t_philo *)philo;
	run = true;
	if (p->id % 2 == 0)
	{
		ft_usleep(p->data->eat_time);
	}
	while (run)
	{
		philo_eat(p);
		print_state(p, SLEEP);
		ft_usleep(p->data->sleep_time);
		think(p->data);
		print_state(p, THINK);
		pthread_mutex_lock(&p->data->check_dead_lock);
		if (p->data->stop_prog_flag)
			run = false;
		pthread_mutex_unlock(&p->data->check_dead_lock);
	}
	return (philo);
}

// bool	run_prog(t_philosophers *data)
// {
// 	//init all threads (philos)
// 	pthread_create(&monitor, NULL, &monitor_routine, NULL);
// 	//init philos and fork for each one, take the prev philo fork as fork1, fork2 - create own
// 	// for first philo put the fork1 at the very end
// 	//create thread for each philo
// }

int	main(int ac, char **av)
{
	char				*err;
	t_philosophers		data;

	err = "Error: program init failed\n";
	if (err_check(ac, av))
		return (1);
	if (!prog(av, &data))
	{
		write (2, err, ft_strlen(err));
		return (1);
	}
	return (0);
}
