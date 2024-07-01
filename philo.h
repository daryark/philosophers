/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:59:06 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/01 18:36:29 by dyarkovs         ###   ########.fr       */
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

#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RE  "\033[0m"

// #include "libft.h"

typedef enum        s_act
{
    EAT,
    SLEEP,
    THINK,
    FORK,
    DIE
}                   t_act;

typedef struct s_philo  t_philo;

typedef struct      s_fork
{
    bool            taken;
    pthread_mutex_t mtx;
}                   t_fork;

typedef struct      s_philosophers
{
    int             n_philos;
    t_philo         *philo_arr;
    t_fork          *fork_arr;
    long            die_time;
    long            eat_time;
    long            sleep_time;
    int             n_meals;
    bool            has_died;
    long            prog_start_time;
}                   t_philosophers;

typedef struct      s_philo
{
    pthread_t       thread;
    t_fork          *r_fork;
    t_fork          *l_fork;
    int             id;
    int             meals_ate;
    long            ate_last_time;
    t_philosophers  *data;
}                   t_philo;

//utils
int     err_check(int ac, char **av);
int     is_digit_loop(char *s);
long	ft_atol(const char *str);
void    print_state(long time_ms, int philo_nb, t_act act);
void    ft_usleep(int ms);
long    gettimeofday_in_mcrsec();

bool    init_prog(char **av, t_philosophers *data);
bool	create_forks(t_fork **arr, int n);
void	init_philos(t_philosophers *data);
bool	create_threads_run(t_philosophers *data);
void    *philo_routine(void *philo);
void    clean_mtx_arr(t_fork **arr);
void    clean_philo_arr(t_philo **arr);
#endif