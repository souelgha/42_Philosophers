/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:06:42 by sonia             #+#    #+#             */
/*   Updated: 2024/07/10 10:39:06 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_control(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
	{
		if (check_all_dead(philos) == 1 || check_meal_finish(philos) == 1)
			return (args);
		usleep(50);
	}
	return (args);
}

int	check_timeover(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() >= (philo->last_meal + philo->time_to_die))
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_all_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_philo)
	{
		if (check_timeover(&philos[i]) == 1)
		{
			print_message(&philos[i], "died");
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	philo_full(t_philo *philo)
{
	if (philo->nb_limits_meal == -1)
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->nb_meal == philo->nb_limits_meal)
	{
		philo->philo_full = 1;
		pthread_mutex_unlock(&philo->meal_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return ;
}

int	check_meal_finish(t_philo *philos)
{
	int	i;
	int	full_meal;

	i = 0;
	full_meal = 0;
	if (philos[0].nb_limits_meal == -1)
		return (0);
	while (i < philos[0].nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].philo_full == 1)
			full_meal += 1;
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	if (full_meal == philos[0].nb_philo)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}
