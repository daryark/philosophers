/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:12:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/27 16:06:50 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(const char *str)
{
	int			sign;
	long         nb;

	sign = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
    return (nb * sign);
}

static int is_digit_loop(char *s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        if (!(s[i] >='0' && s[i] <= '9') && !(s[i] == '-' || s[i] == '+'))
            return (0);
    }
    return (i);
}

int err_check(int ac, char **av)
{
    long    n;

    if (ac != 5 && ac != 6)
        return (printf("Wrong nubmer of arguments!\n"));
    while (--ac)
    {
        n = ft_atol(av[ac]);
        if (!is_digit_loop(av[ac]) || n < INT_MIN || n > INT_MAX)
            return (printf("Only numeric parameters of 'int' type accepted\n"));
        if (ac == 5 && n < 0)
            return (printf("Philosopher cannot eat less than 0 times\n"));
        if (ac == 1 && n > 200)
            return (printf("You should not run the program with more than 200 philosophers\n"));
        if (n <= 0 && ac != 5)
            return (printf("Values more than 0 accepted, but for the 5 param - can be 0\n"));
        if (n < 60 && (ac == 2 || ac == 3 || ac == 4))
            return (printf("Pass time to eat, sleep and die more than 60ms\n"));
    }
    printf("Error check done\n");
    return (0);
}

long    gettimeofday_in_mcrsec(void)
{
    struct timeval  tv;

    gettimeofday(&tv, 0);
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void    ft_usleep(int ms)
{
    long    start;
    long    now;
    
    start = gettimeofday_in_mcrsec();
    now = start;
    while (now - start < ms * 1000)
        now  = gettimeofday_in_mcrsec();
}