/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:44:32 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 19:03:59 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    clean_mtx_arr(mtx_t **arr)
{
    int i;

    i = -1;
    while (arr[++i])
        pthread_mutex_destroy(&(*arr)[i]);
    free(*arr);
    *arr = NULL;
    printf(RED "clean mtx fn (pthread mutex destroy)\n" RE);
}

void    clean_philo_arr(t_philo **arr)
{
    int i;

    i = -1;
    while (arr[++i])
        pthread_join(arr[i]->thread, NULL);
    free(*arr);
    *arr = NULL;
    printf(RED "clean fn (pthread join)\n"  RE);
}

void    stop_prog(t_philosophers *data)
{
    // printf("in stop prog fn\n");
    clean_mtx_arr(&data->fork_arr);
    // printf("philo arr cleaned\n");
	clean_philo_arr(&data->philo_arr);
    // printf("joined threads\n");
    pthread_mutex_destroy(&data->print_mtx);
	printf("cleaned prog\n");
}