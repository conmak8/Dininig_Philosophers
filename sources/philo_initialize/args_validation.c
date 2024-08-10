/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:56:03 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/10 04:00:14 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	input_is_valid(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (print_error("Incorrect number of arguments\n"), 0);
	++argv;
	while (*argv)
	{
		if (!is_valid_number(*argv))
			return (print_error("Incorrect character in arguments\n"), 0);
		if (ft_atoll(*argv) <= 0)
			return (print_error("Cannot have zero or \
			negative in arguments\n"), 0);
		argv++;
	}
	return (true);
}