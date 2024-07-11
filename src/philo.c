/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonia <sonia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:19:00 by sonouelg          #+#    #+#             */
/*   Updated: 2024/07/11 09:31:42 by sonia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_data			*data;
	t_philo			*philos;

	if (!check_args(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!data || !forks || !philos)
	{
		free_malloc(data, philos, forks);
		return (0);
	}
	init_forks(forks, argv);
	init_data(data, philos);
	iphilos(philos, data, forks, argv);
	create_thread(data, forks);
	dest_mutxs(data, forks, philos);
	free_malloc(data, philos, forks);
	return (0);
}
