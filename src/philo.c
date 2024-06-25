/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/25 21:56:48 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	printf("Thread worked\n");
	//*close lock
	ph->meals_ate += 1;
	sleep(3);
	printf("End of thread, %d\n", ph->meals_ate);
	//*open lock
    return ((void *)philo);
}

static void	init_philo(int n, t_philo **arr)
{
	*arr = malloc(sizeof(t_philo) * n);
	while (n-- > 0)
	{
		pthread_create(&arr[n]->thread, NULL, &routine, &arr[n]);
		arr[n]->id = n;
		arr[n]->meals_ate = 0;
		arr[n]->ate_last_time = 0;
	}
}

static bool init_prog(char **av, t_philosophers *data)
{
	int	i;

	data->n_philos = (int)ft_atol(av[1]);
	data->die_time = ft_atol(av[2]);
	data->sleep_time = ft_atol(av[3]);
	data->eat_time = ft_atol(av[4]);
	data->n_meals = -1;
	if (av[5])
		data->n_meals = (int)ft_atol(av[5]);
	// data->philo_arr = NULL;
	i = -1;
	while (++i < data->n_philos)
		init_philo(data->n_philos, &data->philo_arr);
	// if (data->philo_arr == NULL)
	// {
	// 	printf("Allcation failed\n");
	// 	return (false);
	// }
	return (true);
}

int	main(int ac, char **av)
{
	t_philosophers		data;
	// pthread_t	thrd1, thrd2;
	// int		*n_arr;
	
	//*err check
	if (err_check(ac, av))
		return (1);
	//*fill the table
	printf("after err check\n");
	if (!init_prog(av, &data))
		return (1);
	//*start dinner
	//*clean
	// pthread_create(&thrd1, NULL, &routine, (void *)&n);
        // pthread_create(&thrd2, NULL, &routine, (void *)&n);
        // pthread_join(thrd1, NULL);
        // pthread_join(thrd2, NULL);
	return (0);
}
//pthread_create(&philo.thread, NULL, &routine, &philo);