/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonia <sonia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:39:38 by sonouelg          #+#    #+#             */
/*   Updated: 2024/07/11 10:53:19 by sonia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (check_digit(argv[i]) == 0 || ft_atoi(argv[i]) == -1)
		{
			printf("Invalid Arguments\n");
			return (0);
		}
		if (ft_atoi(argv[i]) == 0)
		{
			if (i == 1)
				printf("No philosopher around table. need at least 1 !\n");
			else if (i == 5)
				printf("No meal on the table. need at least 1 !\n");
			else
				printf("try value > 0 !!!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
