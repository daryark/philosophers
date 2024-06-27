/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:44:32 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/27 16:59:59 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    clean_mtx_arr(t_fork **arr)
{
    int i;

    i = -1;
    while (arr[++i])
        pthread_mutex_destroy(&(*arr)[i].mtx);
    free(*arr);
    *arr = NULL;
}

void    clean_philo_arr(t_philo **arr)
{
    int i;

    i = -1;
    while (arr[++i])
        pthread_join(arr[i]->thread, NULL);
    free(*arr);
    *arr = NULL;
}