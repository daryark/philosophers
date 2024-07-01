/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:12:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/01 18:38:39 by dyarkovs         ###   ########.fr       */
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

int is_digit_loop(char *s)
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

void    print_state(long time_ms, int philo_nb, t_act act)
{
    char *msg;

    if (act == DIE)
        msg = "died";
    else if (act == EAT)
        msg = "is eating";
    else if (act == SLEEP)
        msg = "is sleeping";
    else if (act == THINK)
        msg = "is thinking";
    else if (act == FORK)
        msg = "has taken a fork";
    else
        msg = "if anyone knows what the hell is he doin ???";
    printf("%ld %d  %s\n", time_ms, philo_nb, msg);
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