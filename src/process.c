/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:28:50 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/03 16:42:26 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool take_fork(t_philo *philo, mtx_t *fork)
{
    pthread_mutex_lock(fork);
    if (check_full(philo->data) || check_dead(philo))
        return (false);
    print_state(philo, FORK);
    return (true);
}

void    philo_meal_count(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mtx);
    if (philo->data->n_meals > 0)
        philo->meals_ate++;
    if (philo->data->n_meals > 0 && philo->data->n_meals <= philo->meals_ate)
        philo->data->full_philos++;
    pthread_mutex_unlock(&philo->data->print_mtx);
}

bool    philo_eat(t_philo *philo)
{
    if (!take_fork(philo, philo->fork1))
    {
        pthread_mutex_unlock(philo->fork1);
        return (false);
    }
    if (philo->data->n_philos == 1)
        return (monitor_usleep(philo->data->die_time, philo));
    if (!take_fork(philo, philo->fork2))
    {
        pthread_mutex_unlock(philo->fork2);
        pthread_mutex_unlock(philo->fork1);
        return (false);
    }
    print_state(philo, EAT);
    philo->ate_last_time = gettimeofday_in_mcs();
    if (!monitor_usleep(philo->data->eat_time, philo))
    {
        pthread_mutex_unlock(philo->fork2);
        pthread_mutex_unlock(philo->fork1);
        return (false);
    }
    philo_meal_count(philo);
    pthread_mutex_unlock(philo->fork2);
    pthread_mutex_unlock(philo->fork1);
    return (!check_dead(philo) && !check_full(philo->data));
}

bool    philo_sleep(t_philo *philo)
{
    print_state(philo, SLEEP);
    if (!monitor_usleep(philo->data->sleep_time, philo))
        return (false);
    return (!check_dead(philo) && !check_full(philo->data));
}
