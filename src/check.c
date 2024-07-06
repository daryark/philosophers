/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:43:52 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 02:55:33 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool    check_dead(t_philosophers *data)
{
   int  i;
   long doesnt_eat_time;

   i = -1;
    while (++i < data->n_philos)
    {
        pthread_mutex_lock(&data->meal_lock);
        doesnt_eat_time = gettimeofday_in_mcs() - data->philos[i].ate_last_time;
        pthread_mutex_unlock(&data->meal_lock);
        // pthread_mutex_lock(&data->print_lock);
        // printf(YELLOW "ch_d:%d  " RE, i);
        // pthread_mutex_unlock(&data->print_lock);
        pthread_mutex_lock(&data->check_dead_lock);
        if (doesnt_eat_time > data->die_time)
        {
            data->stop_prog_flag = true;
            pthread_mutex_unlock(&data->check_dead_lock);
            pthread_mutex_lock(&data->print_lock);
            printf(RED "\ndoesnt_eat_time: %ld, data->die_time: %ld\n" RE, doesnt_eat_time, data->die_time);
            printf(RED "CHECK_DEAD stop_prog_flag:%d\n" RE, data->stop_prog_flag);
            pthread_mutex_unlock(&data->print_lock);
            print_state(&data->philos[i], DIE);
            return (true);
        }
        pthread_mutex_unlock(&data->check_dead_lock);
    }
    return (false);
}

bool	check_full_all(t_philosophers *data)
{
	int  i;
    int  n_full;

    n_full = 0;
    i = -1;
    pthread_mutex_lock(&data->meal_lock);
    if (data->philos[0].meals_left == -1)
        return (pthread_mutex_unlock(&data->meal_lock), false);
    pthread_mutex_lock(&data->check_dead_lock);
    while (++i < data->n_philos)
    {
        // pthread_mutex_lock(&data->print_lock);
        // printf(GREEN "ch_fl:%d " RE, i);
        // pthread_mutex_unlock(&data->print_lock);
        if (data->philos[i].meals_left == 0)
            n_full++;
    }
    if (n_full == data->n_philos)
    {
        data->stop_prog_flag = true;
        pthread_mutex_lock(&data->print_lock);
        printf(GREEN "CHECK FULL stop_prog_flag:%d, n_full: %d, n_philos: %d\n" RE, data->stop_prog_flag, n_full, data->n_philos);
        pthread_mutex_unlock(&data->print_lock);
        return (pthread_mutex_unlock(&data->check_dead_lock), pthread_mutex_unlock(&data->meal_lock), true);
    }
    return (pthread_mutex_unlock(&data->check_dead_lock), pthread_mutex_unlock(&data->meal_lock), false);
}

//check_dead_lock for both: check_dead & check_full fns as both can change stop_prog_flag
//+meal_lock:check dead/no 
//+meal_lock:check_full/no for loop! to not lock/unlock each time i check philo.is_full
// //*assigned this act to monitor_routine now
// bool    stop_prog(t_philosophers *data)
// {
//     bool stop;

//     pthread_mutex_lock(&data->check_dead_lock);
//     stop = false;
//     if (check_dead(data) || check_full_all(data))
//         stop = true;
//     return (pthread_mutex_unlock(&data->check_dead_lock), stop);
// }

int err_check(int ac, char **av)
{
    long    n;
    char    *format;

    format = "STRUCTURE\n./philo <n_philos> <die_ms> <eat_ms> <sleep_ms>\
    [opt:<times to eat>]\n";
    if (ac != 5 && ac != 6)
        return (printf("Wrong nubmer of arguments!\n%s", format));
    while (--ac)
    {
        n = ft_atol(av[ac]);
        if (!is_digit_loop(av[ac]) || n < INT_MIN || n > INT_MAX)
            return (printf("Only numeric parameters of 'int' type accepted\n"));
        if (ac == 5 && n <= 0)
            return (printf("Philosopher cannot eat less than 1 times\n"));
        if (ac == 1 && n > 200)
            return (printf("You should not run the program with more than 200 philos\n"));
        if (n <= 0)
            return (printf("Values more than 0 accepted\n"));
        if (n < 60 && (ac == 2 || ac == 3 || ac == 4))
            return (printf("Pass time to eat, sleep and die more than 60ms\n"));
    }
    return (0);
}
