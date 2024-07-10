/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:37:51 by sonia             #+#    #+#             */
/*   Updated: 2024/07/10 16:14:32 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	supervisor;
	int			i;

	if (pthread_create(&supervisor, NULL, death_control, data->philos))
		return (1);
	i = 0;
	while (i < data->philos[0].nb_philo)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				routine, &data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_join(supervisor, NULL))
		return (1);
	i = 0;
	while (i < data->philos[0].nb_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	while (!check_flag_death(philo))
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (args);
}

int	check_flag_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	print_message(t_philo *philo, char *str)
{
	size_t	delta_t;

	pthread_mutex_lock(philo->print_lock);
	delta_t = get_time() - philo->diner_start;
	if (!check_flag_death(philo))
		printf("%zu %d %s\n", delta_t, philo->philo_id, str);
	pthread_mutex_unlock(philo->print_lock);
}
