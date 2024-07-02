/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:28:50 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 01:52:05 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void take_fork(t_philo *philo, int fork_n, int *has_forks)
{
    (*has_forks)++;
    (void)fork_n;
    // if (fork_n == 1)
    //     philo->fork1->taken = 1;
    // else
    //     philo->fork2->taken = 1;
    print_state(philo->id, FORK);
}
bool    check_dead(t_philo *philo)
{
     if (gettimeofday_in_mcs() - philo->ate_last_time < philo->data->die_time)
        philo->data->is_dead = true;
    return (philo->data->is_dead);
}

void    philo_meal_count(t_philo *philo)
{
    if (philo->data->n_meals > 0)
        philo->meals_ate++;
    if (philo->data->n_meals <= philo->meals_ate)
        philo->data->full_philos++;
}

bool    eat(t_philo *philo)
{
    int has_forks;

    has_forks = 0;
    while (has_forks < 2)
    {
        // if (!philo->fork1->taken)
        pthread_mutex_lock(philo->fork1->mtx);
        take_fork(philo, 1, &has_forks);
        // if (philo->fork2->taken)
        pthread_mutex_lock(philo->fork2->mtx);
        take_fork(philo, 2, &has_forks);
    }
    print_state(philo->id, EAT);
    philo->ate_last_time = gettimeofday_in_mcs();
    if (!monitor_usleep(philo->data->eat_time, philo->data))
        return (false);
    philo_meal_count(philo);
    pthread_mutex_unlock(&(philo->fork2->mtx));
    pthread_mutex_unlock(&(philo->fork1->mtx));
    return (!check_dead(philo));
}

// bool    stop_prog(t_philosophers *data)
// {
//     if (data->is_dead == true)    
//         return (true);
//     return (false);
// }