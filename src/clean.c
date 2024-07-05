/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:44:32 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/05 17:00:58 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void   clean_prog(t_philosophers *data)
{
    int i;

    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philos[i].thread, NULL);
    free(data->philos);
    i = -1;
    while (++i < data->n_philos)
        pthread_mutex_destroy(&data->forks[i].fork);
    free(data->forks);
    pthread_join(data->monitor, NULL);
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->meal_lock);
    pthread_mutex_destroy(&data->check_dead_lock);
}
