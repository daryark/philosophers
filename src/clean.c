/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:44:32 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 21:14:44 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void    clean_mtx_arr(mtx_t **arr, int n)
// {
//     int i;

//     i = -1;
//     while (++i < n)
//     {
//         printf("clean one mtx\n");
//         pthread_mutex_destroy(arr[i]);
//     }
//     printf("cleaned all mtx\n");
//     free(*arr);
//     *arr = NULL;
//     printf(RED "clean mtx fn (pthread mutex destroy)\n" RE);
// }

// void    clean_philo_arr(t_philo **arr, int n)
// {
//     int i;

//     i = -1;
//     while (++i < n)
//         pthread_join(arr[i]->thread, NULL);
//     printf("joined all the threads\n");
//     free(*arr);
//     *arr = NULL;
//     printf(RED "clean fn (pthread join)\n"  RE);
// }

void    stop_prog(t_philosophers *data)
{
    int i;

    printf("in stop prog fn\n");
    i = -1;
    while (++i < data->n_philos)
        pthread_join(data->philo_arr[i].thread, NULL);
    printf("joined all the threads\n");
    free(data->philo_arr);
    data->philo_arr = NULL;
    printf(RED "clean fn (pthread join)\n"  RE);
    printf("joined threads\n");
	i = -1;
    while (++i < data->n_philos)
    {
        printf("clean one mtx\n");
        pthread_mutex_destroy(&data->fork_arr[i]);
    }
    printf("cleaned all mtx\n");
    free(data->fork_arr);
    data->philo_arr = NULL;
    printf(RED "clean mtx fn (pthread mutex destroy)\n" RE);
	pthread_mutex_destroy(&data->print_mtx);
	// clean_philo_arr(&data->philo_arr, data->n_philos);
    // clean_mtx_arr(&data->fork_arr, data->n_philos);
    // printf("destroyed threads\n");
    // pthread_mutex_destroy(&data->print_mtx);
	// printf("cleaned prog\n");
}
