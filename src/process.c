/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:28:50 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 20:48:52 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_fork(t_philo *philo, t_mtx *fork)
{
	safe_mtx(fork, 'l');
	print_state(philo, FORK);
}

static void	leave_forks(t_philo *philo)
{
	safe_mtx(&philo->data->forks[philo->fork2_id - 1].fork, 'u');
	safe_mtx(&philo->data->forks[philo->fork1_id - 1].fork, 'u');
}

static bool	meal_count(t_philo *philo)
{
	if (philo->meals_left == -1)
		return (0);
	if (philo->meals_left > 0)
		philo->meals_left--;
	else
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		leave_forks(philo);
		return (1);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo, &philo->data->forks[philo->fork1_id - 1].fork);
	if (philo->data->n_philos == 1)
	{
		safe_mtx(&philo->data->forks[philo->fork1_id - 1].fork, 'u');
		pthread_mutex_lock(&philo->data->check_dead_lock);
		philo->data->stop_prog_flag = 1;
		pthread_mutex_unlock(&philo->data->check_dead_lock);
		return ;
	}
	take_fork(philo, &philo->data->forks[philo->fork2_id - 1].fork);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->ate_last_time = gettimeofday_in_mcs();
	if (meal_count(philo))
		return ;
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_state(philo, EAT);
	ft_usleep(philo->data->eat_time);
	leave_forks(philo);
}
