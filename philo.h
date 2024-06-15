/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:59:06 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/15 23:24:05 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>

// #include "libft.h"

typedef struct  s_philosophers
{
    int         n_philos;
    long        die_time;
    long        eat_time;
    long        sleep_time;
    int         times_to_eat;
}               t_philosophers;

typedef struct  s_philo
{
    struct s_philo *right_fork;
    struct s_philo *left_fork;
}               t_philo;


//utils
int err_check(int ac, char **av);
long long	ft_atol(const char *str);
#endif