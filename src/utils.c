/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:12:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/07/06 20:24:19 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_philo *philo, t_act act)
{
	char	*msg;

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
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->check_dead_lock);
	if (philo->data->stop_prog_flag && act != DIE)
	{
		pthread_mutex_unlock(&philo->data->check_dead_lock);
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check_dead_lock);
	printf("%-8ld %-3d %s\n", gettimefromstart_ms(philo->data->prog_start_time),
		philo->id, msg);
	pthread_mutex_unlock(&(philo->data->print_lock));
}

long	ft_atol(const char *str)
{
	int		sign;
	long	nb;

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

int	is_digit_loop(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && !(s[i] == '-' || s[i] == '+'))
			return (0);
	}
	return (i);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return ((size_t)i);
}

//d - dead check: time_since_last_meal, time_to_die
//f - full all check: n_full, n_philos
//L - lock fork:  status, fork_id
//U - unlock fork: status, fork_id
//m - meals_left, philo_id
void	debug_print(mtx_t *print_lock, char fn_name, int a, int b)
{
	pthread_mutex_lock(print_lock);
	if (fn_name == 'd')
		printf(RED_F "\nCHECK_DEAD\ntime: %d, die_time: %d\n" RE, a, b);
	else if (fn_name == 'f')
		printf(GREEN "\nCHECK FULL: n_full: %d, n_philos:%d\n " RE, a, b);
	else if (fn_name == 'L')
		printf(MAGENTA_F "%c err: %d, id: %d " RE, fn_name, a, b);
	else if (fn_name == 'U')
		printf(YELLOW_F "%c id: %d " RE, fn_name, b);
	else if (fn_name == 'm')
		printf(GREEN "ml_left: %d, ph_id: %d" RE, a, b);
	pthread_mutex_unlock(print_lock);
}
