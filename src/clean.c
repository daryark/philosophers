/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:44:32 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/03 15:38:30 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    stop_prog(t_philosophers *data)
{
    int i;

    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philo_arr[i].thread, NULL);
    free(data->philo_arr);
    data->philo_arr = NULL;
	i = -1;
    while (++i < data->n_philos)
        pthread_mutex_destroy(&data->fork_arr[i]);
    free(data->fork_arr);
    data->philo_arr = NULL;
	pthread_mutex_destroy(&data->print_mtx);
}
