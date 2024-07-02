/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:07:26 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 20:01:58 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long    gettimeofday_in_mcs(void)
{
    struct timeval  tv;

    gettimeofday(&tv, 0);
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}


long gettimefromstart_ms(long start_mcs)
{
    return ((gettimeofday_in_mcs() - start_mcs) / 1000);
}

bool    monitor_usleep(int mcs, t_philo *philo)
{
    long    start;
    long    now;
    
    start = gettimeofday_in_mcs();
    now = start;
    while (now - start < mcs)
    {
        if (philo->data->full_philos == philo->data->n_philos)
            printf(GREEN "full all\n" RE);
        if (check_dead(philo))
        {
            if (philo->data->is_dead)
            {
                pthread_mutex_unlock(&(philo->data->print_mtx));
                printf(RED "DEAD" RE);
            }
            return (false);
        pthread_mutex_lock(&(philo->data->print_mtx));
        if (philo->data->full_philos == philo->data->n_philos)
        {
            pthread_mutex_unlock(&philo->data->print_mtx);
            return (false);
        }
        // pthread_mutex_unlock(&philo->data->print_mtx);
        }
        now  = gettimeofday_in_mcs();
    }
    return (true);
}
