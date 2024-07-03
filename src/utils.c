/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:12:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/03 18:41:30 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    print_state(t_philo *philo, t_act act)
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
        msg = "what the hell r u doin???";
    pthread_mutex_lock(&(philo->data->print_mtx));
    if (philo->data->is_dead && act != DIE)
    {
        pthread_mutex_unlock(&philo->data->print_mtx);
        return ;
    }
    printf("%-8ld %-3d %s\n", gettimefromstart_ms(philo->data->prog_start_time), philo->id, msg);
    pthread_mutex_unlock(&(philo->data->print_mtx));
}

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
