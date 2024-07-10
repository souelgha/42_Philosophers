/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:45:38 by sonouelg          #+#    #+#             */
/*   Updated: 2024/07/10 16:13:42 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<pthread.h>
# include<limits.h>
# include<sys/time.h>

/***** structures ******/

typedef struct s_philo
{
	pthread_t		thread_id;
	int				nb_philo;
	int				philo_id;	
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				nb_limits_meal;
	int				philo_full;
	size_t			diner_start;
	size_t			last_meal;	
	int				*dead;
	pthread_mutex_t	meal_lock;	
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;	
}	t_philo;

typedef struct s_data
{
	int				end_flag;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
}	t_data;

/****************** fonctions******************/
/********parsing et checks des arguments ****/
int		check_args(int argc, char **argv);
int		check_digit(char *str);

/****************** utils fonctions ************/
int		ft_atoi(char *str);
int		ft_strlen(char *str);
size_t	get_time(void);
int		ft_usleep(size_t routine_ms);

/****************** init functions **************/
void	init_data(t_data *data, t_philo *philos);
void	init_forks(pthread_mutex_t	*forks, char **argv);
void	init_args_philo(t_philo *philo, char **argv);
int		create_thread(t_data *data, pthread_mutex_t *forks);
void	iphilos(t_philo *philos, t_data *dt, pthread_mutex_t *fks, char **argv);
void	philo_full(t_philo *philo);
void	print_message(t_philo *philo, char *str);

/******** error & free management ****************/
void	free_malloc(t_data *data, t_philo *philos, pthread_mutex_t *forks);
void	dest_mutxs(t_data *dt, pthread_mutex_t *fks, t_philo *ps, char *str);

/********** actions &routines *********************/
void	*routine(void *args);
int		check_flag_death(t_philo *philo);
void	philo_thinking(t_philo *philo);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);

/************* monitoring ************************************/
void	*death_control(void *args);
int		check_timeover(t_philo *philo);
int		check_all_dead(t_philo *philos);
int		check_meal_finish(t_philo *philos);

#endif