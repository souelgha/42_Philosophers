/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_mngnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:27:03 by sonouelg          #+#    #+#             */
/*   Updated: 2024/07/09 15:43:28 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dest_mutxs(t_data *dat, pthread_mutex_t *fk, t_philo *pls, char *str)
{
	int	i;

	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	i = 0;
	pthread_mutex_destroy(&dat->print_lock);
	pthread_mutex_destroy(&dat->dead_lock);
	while (i < dat->philos[0].nb_philo)
	{
		pthread_mutex_destroy(&fk[i]);
		pthread_mutex_destroy(&pls[i].meal_lock);
		i++;
	}
}

void	free_malloc(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	if (philos)
		free(philos);
	if (forks)
		free(forks);
	if (data)
		free(data);
}
