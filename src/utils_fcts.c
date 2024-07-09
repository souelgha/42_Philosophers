/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonia <sonia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:29:45 by sonouelg          #+#    #+#             */
/*   Updated: 2024/07/08 22:00:43 by sonia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					i;

	i = 0;
	nb = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			return (-1);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return (nb);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*********** current time ********************** */
size_t	get_time(void)
{
	struct timeval	start;
	size_t			time;

	if (gettimeofday(&start, NULL) == -1)
		write(2, "gettimeofday error\n", 19);
	time = start.tv_sec * 1e3 + start.tv_usec * 1e-3;
	return (time);
}
/*** fonction usleep amelioree  pour eat / sleep time ****/

int	ft_usleep(size_t routine_ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < routine_ms)
		usleep(500);
	return (0);
}
