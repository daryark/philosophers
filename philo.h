/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:59:06 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 16:18:33 by dyarkovs         ###   ########.fr       */
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
#include <errno.h>

#define YELLOW "\033[0;33m"
#define YELLOW_F "\033[1;33m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define MAGENTA "\033[0;35m"
#define MAGENTA_F "\033[1;35m"
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

typedef struct      s_fork
{
    mtx_t           fork;
    int             id;
}                   t_fork;


typedef struct      s_philosophers
{
    int             n_philos;
    long            die_time;
    long            eat_time;
    long            sleep_time;
    t_philo         *philos;
    t_fork          *forks;
    pthread_t       monitor;
    mtx_t           print_lock;
    mtx_t           meal_lock;
    mtx_t           check_dead_lock;
    long            prog_start_time;
    bool            stop_prog_flag; //*checked: full all | died 1
}                   t_philosophers;

typedef struct      s_philo
{
    pthread_t       thread;
    int             fork1_id;
    int             fork2_id;
    int             id;
    int             meals_left; //*checked: is full
    long            ate_last_time;
    t_philosophers  *data;
}                   t_philo;

//utils
int     err_check(int ac, char **av); //*
int     is_digit_loop(char *s); //*
long	ft_atol(const char *str); //*
size_t  ft_strlen(char *s); //*
void    ft_usleep(int mcs); //*
long    gettimeofday_in_mcs(); //*
long    gettimefromstart_ms(long start); //*

void    print_state(t_philo *philo,  t_act act); //*

bool    check_dead(t_philosophers *data); //*
bool    check_full_all(t_philosophers *data); //*
// bool    stop_prog(t_philosophers *data); //*

bool    prog(char **av, t_philosophers *data); //*
void	run_prog(t_philosophers *data, int n_meals); //*
void    clean_prog(t_philosophers *data); //*
void	create_forks(t_fork *arr, int n);//*
void	*monitor_routine(void *data); //*
void    *philo_routine(void *philo); //*
void    philo_eat(t_philo *philo); //*

void    safe_mtx(mtx_t *mtx, int id, t_philo *p, char act);
#endif


//*is_full, n_meals, ate_last_time = meal_lock;
//*stop_prog_flag = check_dead_lock;
//*print_state = print_lock;

//!understand, why monitor is not working
//!so they not die or finish when full