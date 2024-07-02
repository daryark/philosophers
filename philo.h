/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:59:06 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/02 23:50:05 by dyarkovs         ###   ########.fr       */
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

typedef pthread_mutex_t mtx_t;
typedef struct s_philo  t_philo;

typedef enum        s_act
{
    EAT,
    SLEEP,
    THINK,
    FORK,
    DIE
}                   t_act;

typedef struct      s_philosophers
{
    int             n_philos;
    t_philo         *philo_arr;
    mtx_t          *fork_arr;
    long            die_time;
    long            eat_time;
    long            sleep_time;
    int             n_meals;
    int             full_philos;
    bool            is_dead;
    long            prog_start_time;
    mtx_t           print_mtx;
}                   t_philosophers;

typedef struct      s_philo
{
    pthread_t       thread;
    mtx_t          *fork1;
    mtx_t          *fork2;
    int             id;
    int             meals_ate;
    bool            is_full;
    long            ate_last_time;
    t_philosophers  *data;
}                   t_philo;

//utils
int     err_check(int ac, char **av);
int     is_digit_loop(char *s);
long	ft_atol(const char *str);
void    print_state(t_philo *philo,  t_act act);
bool    monitor_usleep(int mcs, t_philo *philo);
bool    check_dead(t_philo *philo);
bool    check_full(t_philosophers *data);
long    gettimeofday_in_mcs();
long    gettimefromstart_ms(long start);

bool    init_prog(char **av, t_philosophers *data);
void	init_philos(t_philosophers *data);
void	create_forks(mtx_t **arr, int n);
void	create_threads(t_philosophers *data);
void    *philo_routine(void *philo);
bool    philo_eat(t_philo *philo);
bool    philo_sleep(t_philo *philo);
void    stop_prog(t_philosophers *data);
#endif