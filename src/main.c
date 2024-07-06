/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 20:10:16 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Monitor philos while they run, until: (one is_dead) or all are full
// sleeps for 0.5ms to have less load no cpu with constant lock/unlock in checks
void	*monitor_routine(void *data)
{
	t_philosophers	*d;
	bool			run;

	d = (t_philosophers *)data;
	run = true;
	while (run)
	{
		if (check_dead(d))
			run = false;
		if (check_full_all(d))
			run = false;
		ft_usleep(500);
	}
	return (data);
}

void	*philo_routine(void *philo)
{
	t_philo	*p;
	bool	run;

	p = (t_philo *)philo;
	run = true;
	if (p->id % 2 == 0)
		ft_usleep(p->data->eat_time);
	while (run)
	{
		philo_eat(p);
		print_state(p, SLEEP);
		ft_usleep(p->data->sleep_time);
		print_state(p, THINK);
		ft_usleep(1000);
		pthread_mutex_lock(&p->data->check_dead_lock);
		if (p->data->stop_prog_flag)
			run = false;
		pthread_mutex_unlock(&p->data->check_dead_lock);
	}
	return (philo);
}

int	main(int ac, char **av)
{
	char			*err;
	t_philosophers	data;

	err = "Error: program init failed\n";
	if (DEBUG)
		printf(GREEN "Debug mode is enabled\n" RE);
	if (err_check(ac, av))
		return (1);
	if (!prog(av, &data))
	{
		write(2, err, ft_strlen(err));
		return (1);
	}
	return (0);
}
