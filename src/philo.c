/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:05:09 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/14 16:25:04 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*routine(void *n)
{
	long	*res;

	res = (long *)n;
	*res += 1;
	printf("Thread worked\n");
	sleep(3);
	printf("End of thread, %ld\n", *res);
    return ((void *)res);
}

int	main(int ac, char **av)
{
	pthread_t	thrd1, thrd2;
	long		n;
	

	(void)av;
	(void)thrd2;
	if (err_check(ac, av))
		return (1);
	if (ac == 5 || ac == 6)
	{
		n = 1;
		printf("5 of 6 args received\n");
        pthread_create(&thrd1, NULL, &routine, (void *)&n);
        // pthread_create(&thrd2, NULL, &routine, (void *)&n);
        pthread_join(thrd1, NULL);
        // pthread_join(thrd2, NULL);
	}
	else
		printf("Not valid amount of arguments\n");
	return (0);
}