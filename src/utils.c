/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:12:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/14 17:13:28 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_atol(const char *str)
{
	int			sign;
	long long	nb;

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
    return (1);
}

int err_check(int ac, char **av)
{
    long    n;

    if (ac != 5 && ac != 6)
        return (printf("Wrong nubmer of arguments!\n"));
    while (--ac)
    {
        if (!is_digit_loop(av[ac]))
            return (printf("Only numeric parameters accepted\n"));
        n = ft_atol(av[ac]);
        if (ac == 5 && n < 0)
            return (printf("Philosopher cannot eat less than 0 times\n"));
        if (ac == 1 && !(n > 0 && n <= 200))
            return (printf("Wrong amount of philosopers, enter value from 1 to 200\n"));
        if (n <= 0 && ac != 5)
            return (printf("Values more than 0 accepted, but for the 5 param - can be 0\n"));
    }
    return (0);
}