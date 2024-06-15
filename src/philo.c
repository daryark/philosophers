/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/15 23:27:35 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// static void	*routine(void *n)
// {
// 	long	*res;

// 	res = (long *)n;
// 	*res += 1;
// 	printf("Thread worked\n");
// 	sleep(3);
// 	printf("End of thread, %ld\n", *res);
//     return ((void *)res);
// }

static bool init_prog(int ac, char **av, t_philosophers *data)
{
	(void)ac; //if i need it in some other inits?
	data = NULL;
	data->n_philos = ft_atol(av[1]);
	data->die_time = ft_atol(av[2]);
	data->sleep_time = ft_atol(av[3]);
	data->eat_time = ft_atol(av[4]);
	data->times_to_eat = -1;
	if (av[5])
		data->times_to_eat = ft_atol(av[5]);
	if (data == NULL)
	{
		printf("Allcation failed\n");
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	// pthread_t	thrd1, thrd2;
	// int		*n_arr;
	
	if (err_check(ac, av))
		return (1);
	if (!init_prog(ac, av, &data))
		return (1);
	// pthread_create(&thrd1, NULL, &routine, (void *)&n);
        // pthread_create(&thrd2, NULL, &routine, (void *)&n);
        // pthread_join(thrd1, NULL);
        // pthread_join(thrd2, NULL);
	return (0);
}