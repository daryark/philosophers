/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:28:50 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 20:24:35 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//*FOR FORKS to track if no err lock/unlock
void	safe_mtx(mtx_t *mtx, int id, t_philo *p, char act)
{
	int	status;

	status = 0;
	if (act == 'L')
		status = pthread_mutex_lock(mtx);
	else if (act == 'U')
		status = pthread_mutex_unlock(mtx);
	if (DEBUG)
		debug_print(&p->data->print_lock, act, status, id);
}

static void	take_fork(t_philo *philo, mtx_t *fork, int id)
{
	safe_mtx(fork, id, philo, 'L');
	print_state(philo, FORK);
}

static void	leave_forks(t_philo *philo)
{
	safe_mtx(&philo->data->forks[philo->fork2_id - 1].fork, philo->fork2_id,
		philo, 'U');
	safe_mtx(&philo->data->forks[philo->fork1_id - 1].fork, philo->fork1_id,
		philo, 'U');
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo, &philo->data->forks[philo->fork1_id - 1].fork,
		philo->fork1_id);
	if (philo->data->n_philos == 1)
		{
			safe_mtx(&philo->data->forks[philo->fork1_id - 1].fork, philo->fork1_id,
				philo, 'U');
			pthread_mutex_lock(&philo->data->check_dead_lock);
			philo->data->stop_prog_flag = 1;
			pthread_mutex_unlock(&philo->data->check_dead_lock);
			return ;
		}
	take_fork(philo, &philo->data->forks[philo->fork2_id - 1].fork,
		philo->fork2_id);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->ate_last_time = gettimeofday_in_mcs();
		if (philo->meals_left != -1)
	{
		if (philo->meals_left > 0)
			philo->meals_left--;
		else
		{
			pthread_mutex_unlock(&philo->data->meal_lock);
			leave_forks(philo);
			return ;
		}
        if (DEBUG)
			debug_print(&philo->data->print_lock, 'm', philo->meals_left, philo->id);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_state(philo, EAT);
	ft_usleep(philo->data->eat_time);
	leave_forks(philo);
}
