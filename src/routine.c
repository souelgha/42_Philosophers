/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:22:27 by sonia             #+#    #+#             */
/*   Updated: 2024/07/10 17:05:51 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
	if (philo->time_to_eat >= philo->time_to_sleep)
		ft_usleep(philo->time_to_eat - philo->time_to_sleep + 1);
}

void	philo_eating(t_philo *philo)
{
	take_forks(philo);
	if (philo->nb_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		print_message(philo, "died");
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_meal += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	philo_full(philo);
	ft_usleep(philo->time_to_eat);
	drop_forks(philo);
}

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		if (philo->nb_philo == 1)
			return ;
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}	
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}	
}
