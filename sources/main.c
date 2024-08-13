/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:35:27 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/13 21:09:13 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_sim_data	data;

	if (!input_is_valid(argc, argv))
	{
		printf("Invalid input\n");
		return (EXIT_FAILURE);
	}
	if (!initialize_data(argc, argv, &data))
	{
		printf("Initialization failed\n");
		return (EXIT_FAILURE);
	}
	if (!launch_threads(&data, data.philosophers))
	{
		printf("Failed to launch threads\n");
		return (EXIT_FAILURE);
	}
	ft_cleanup(&data);
	return (0);
}
