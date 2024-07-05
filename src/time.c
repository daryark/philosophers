/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:07:26 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/05 16:37:46 by dyarkovs         ###   ########.fr       */
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

// bool    monitor_usleep(int mcs, t_philo *philo)
// {
//     long    start;
//     long    now;
    
//     start = gettimeofday_in_mcs();
//     now = start;
//     while (now - start < mcs)
//     {
//         if (check_dead(philo) || check_full(philo->data))
//             return (false);
//         now  = gettimeofday_in_mcs();
//     }
//     return (true);
// }

void ft_usleep(int mcs)
{
    long start;
    long now;
    long elapsed;

    start = gettimeofday_in_mcs();
    while (true)
    {
        now = gettimeofday_in_mcs();
        elapsed = now - start;
        if (elapsed >= mcs)
            break;
        if (elapsed > 1000)
            usleep(1000);
        else
            usleep(mcs - elapsed);
    }
}

