/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:43:52 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/03 16:26:55 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool    check_dead(t_philo *philo)
{
    long    diff;

    pthread_mutex_lock(&philo->data->print_mtx);
    diff = gettimeofday_in_mcs() - philo->ate_last_time;
     if (diff > philo->data->die_time || philo->data->is_dead)
    {
        if (!philo->data->is_dead)
        {
            philo->data->is_dead = true;
        pthread_mutex_unlock(&philo->data->print_mtx);
            print_state(philo, DIE);
        pthread_mutex_lock(&philo->data->print_mtx);
        }
        pthread_mutex_unlock(&philo->data->print_mtx);
        return (true);
    }
    pthread_mutex_unlock(&philo->data->print_mtx);
    return (false);
}

bool	check_full(t_philosophers *data)
{
	pthread_mutex_lock(&data->print_mtx);
	if (data->n_philos == data->full_philos)
	{
		pthread_mutex_unlock(&data->print_mtx);
		return (true);
	}
	pthread_mutex_unlock(&data->print_mtx);
	return (false);
}

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
