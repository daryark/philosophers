/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:59:06 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/17 21:22:49 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>

// #include "libft.h"
typedef struct      s_philo;

typedef struct      s_philosophers
{
    int             n_philos;
    t_philo         *philo_arr;
    int             die_time;
    int             eat_time;
    int             sleep_time;
    int             n_meals;
}                   t_philosophers;

typedef struct      s_philo
{
    pthread_t       thread;
    int             id;
    int             meals_ate;
    long            ate_last_time;
    t_philosophers  *data;
}                   t_philo;

//utils
int     err_check(int ac, char **av);
long	ft_atol(const char *str);
#endif