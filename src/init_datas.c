/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:06:50 by sonouelg          #+#    #+#             */
/*   Updated: 2024/07/10 16:15:20 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, t_philo *philos)
{
	data->end_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
}

void	init_forks(pthread_mutex_t	*forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_args_philo(t_philo *philo, char **argv)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	if (ft_atoi(argv[2]) > ft_atoi(argv[3]))
		philo->time_to_eat = ft_atoi(argv[3]);
	else
		philo->time_to_eat = ft_atoi(argv[2]);
	if (ft_atoi(argv[2]) > ft_atoi(argv[4]))
		philo->time_to_sleep = ft_atoi(argv[4]);
	else
		philo->time_to_sleep = ft_atoi(argv[2]);
	if (argv[5])
		philo->nb_limits_meal = ft_atoi(argv[5]);
	else
		philo->nb_limits_meal = -1;
}

void	iphilos(t_philo *philos, t_data *dt, pthread_mutex_t *fks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{	
		philos[i].philo_id = i + 1;
		philos[i].nb_meal = 0;
		philos[i].philo_full = 0;
		init_args_philo(&philos[i], argv);
		philos[i].diner_start = get_time();
		philos[i].last_meal = get_time();
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		philos[i].print_lock = &dt->print_lock;
		philos[i].dead_lock = &dt->dead_lock;
		philos[i].dead = &dt->end_flag;
		philos[i].left_fork = &fks[i];
		if (i == 0)
			philos[i].right_fork = &fks[philos[i].nb_philo - 1];
		else
			philos[i].right_fork = &fks[i - 1];
		i++;
	}
}
