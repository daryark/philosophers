/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:28:50 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/05 18:40:49 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void take_fork(t_philo *philo, mtx_t *fork, int id)
{
    (void)id;
    pthread_mutex_lock(fork);
    // pthread_mutex_lock(&philo->data->print_lock); //!
    // printf(GREEN "%d" RE, id); //!
    // pthread_mutex_unlock(&philo->data->print_lock); //!
    print_state(philo, FORK);
}

static void leave_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->fork2_id].fork);
    pthread_mutex_unlock(&philo->data->forks[philo->fork1_id].fork);
}

void    philo_eat(t_philo *philo)
{
    take_fork(philo, &philo->data->forks[philo->fork1_id].fork, philo->fork1_id); //*f1
    if (philo->data->n_philos == 1)
    {
        pthread_mutex_unlock(&philo->data->forks[philo->fork1_id].fork);
        return ;
    }
    take_fork(philo, &philo->data->forks[philo->fork2_id].fork, philo->fork2_id); //*f2
    pthread_mutex_lock(&philo->data->meal_lock); //*eat last time
    if (philo->meals_left != -1)
    {
        pthread_mutex_lock(&philo->data->print_lock); //!
        printf(GREEN "%d" RE, philo->meals_left); //!
        pthread_mutex_unlock(&philo->data->print_lock); //!
        if (philo->meals_left > 0)
            philo->meals_left--;
        else
        {
            pthread_mutex_unlock(&philo->data->meal_lock);
            leave_forks(philo);
            return ;
        }
    }
    pthread_mutex_unlock(&philo->data->meal_lock);
    print_state(philo, EAT);
    ft_usleep(philo->data->eat_time);
    leave_forks(philo);
    }

