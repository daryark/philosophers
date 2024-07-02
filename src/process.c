/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:28:50 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 03:00:07 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void take_fork(t_philo *philo, mtx_t *fork)
{
    pthread_mutex_lock(fork);
    print_state(philo, FORK);
}
bool    check_dead(t_philo *philo)
{
    long    diff;

    diff = gettimeofday_in_mcs() - philo->ate_last_time;
     if (diff > philo->data->die_time)
        philo->data->is_dead = true;
    // printf("start: %ld, last ate: %ld, diff: %ld is_dead: %d\n", gettimeofday_in_mcs(), philo->ate_last_time, diff, philo->data->is_dead);
    return (philo->data->is_dead);
}

void    philo_meal_count(t_philo *philo)
{
    if (philo->data->n_meals > 0)
        philo->meals_ate++;
    if (philo->data->n_meals <= philo->meals_ate)
        philo->data->full_philos++;
}

bool    philo_eat(t_philo *philo)
{
    take_fork(philo, philo->fork1);
    take_fork(philo, philo->fork2);
    print_state(philo, EAT);
    philo->ate_last_time = gettimeofday_in_mcs();
    if (!monitor_usleep(philo->data->eat_time, philo))
        return (false);
    philo_meal_count(philo);
    pthread_mutex_unlock(philo->fork2);
    pthread_mutex_unlock(philo->fork1);
    return (!check_dead(philo));
}

bool    philo_sleep(t_philo *philo)
{
    print_state(philo, SLEEP);
    if (!monitor_usleep(philo->data->sleep_time, philo))
        return (false);
    return (check_dead(philo));
}
