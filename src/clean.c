/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:44:32 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 21:27:25 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    stop_prog(t_philosophers *data)
{
    int i;

    printf("in stop prog fn\n");
    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philo_arr[i].thread, NULL);
    free(data->philo_arr);
    data->philo_arr = NULL;
    printf(RED "clean fn (pthread join)\n"  RE);
	i = -1;
    while (++i < data->n_philos)
        pthread_mutex_destroy(&data->fork_arr[i]);
    printf("cleaned all mtx\n");
    free(data->fork_arr);
    data->philo_arr = NULL;
    printf(RED "clean mtx fn (pthread mutex destroy)\n" RE);
	pthread_mutex_destroy(&data->print_mtx);
}
