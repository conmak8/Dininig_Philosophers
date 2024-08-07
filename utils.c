/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:41:08 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 17:01:22 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int a)
{
	if (a > 47 && a < 58)
		return (1);
	return (0);
}
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++ ;
	return (i);
}

int	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return(EXIT_FAILURE);
}

bool	input_is_valid(int argc, char **argv)
{
	size_t i;
	// handle args number validity
	if (argc != 5 && argc != 6)
		return(print_error("Incorrect number of arguments\n"));
	// handle args type validity
	while (*argv)
	{
		i = 0;
		
		if (!is_valid_number(argv[i]))
			return(print_error("Incorrect character in arguments\n"));
		i++;
		if (ft_atoi(*argv) == 0)
			return(print_error("Cannot have zero in arguments\n"));
		argv++;
	}
	return(true);
}