/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:35:27 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/09 13:35:39 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim_data		data;
	// t_philosopher	*philosophers;
	

	printf("Starting simulation with %d philosophers...!!!!\n", argc > 1 ? atoi(argv[1]) : 0);

	// handle arguments num and validation
	if (!input_is_valid(argc, argv)) {
		printf("Invalid input\n");
		return(EXIT_FAILURE);
	}
	// initialize data
	if (!initialize_data(argc, argv, &data)) 
	{
		printf("Initialization failed\n");
		return(EXIT_FAILURE);
	}

	if (!launch_threads(&data, data.philosophers)) {
		printf("Failed to launch threads\n");
		return (EXIT_FAILURE);
	}
	
	printf("Simulation completed successfully\n");
	return(0);
}




// int	main(int argc, char **argv)
// {
// 	t_sim_data		data;
// 	t_philosopher	*philosophers;
	
// 	// handle arguments num and validation
// 	if (!input_is_valid(argc, ++argv))
// 		return(EXIT_FAILURE);
// 	// initialize data
// 	if (!initilize_data(argc, argv, &data))
// 		return(EXIT_FAILURE);

// 	philosophers = data.philosophers;
	
// 	if (!launch_threads(&data, philosophers))
// 		return (EXIT_FAILURE);

	
	
// 	return(0);
// } 