/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:22:27 by sonia             #+#    #+#             */
/*   Updated: 2024/07/09 17:03:18 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	size_t	delta_t;

	pthread_mutex_lock(philo->print_lock);
	delta_t = get_time() - philo->diner_start;
	if (!check_flag_death(philo))
		printf("%zu %d %s\n", delta_t, philo->philo_id, str);
	pthread_mutex_unlock(philo->print_lock);
}

void	philo_sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
	ft_usleep(2);
}

void	philo_eating(t_philo *philo)
{
	take_forks(philo);
	print_message(philo, "is eating");
	// if (philo->nb_philo == 1)
	// 	{
	// 		ft_usleep(philo->time_to_die);
	// 		print_message(philo, "died");
	// 		pthread_mutex_lock(philo->dead_lock);
	// 		*philo->dead = 1;
	// 		pthread_mutex_unlock(philo->dead_lock);
	// 		return ;
	// 	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->nb_meal += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	philo_full(philo);
	drop_forks(philo);
}
void take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);;
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
	
}

void drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
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

