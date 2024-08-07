/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:35:27 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 19:39:07 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim_data data;
	t_philosopher	*philosophers;
	
	// handle arguments num and validation
	if(!input_is_valid(argc, ++argv))
		return(EXIT_FAILURE);
	// initialize data
	if(!initilize_data(argc, argv, &data));
		return(EXIT_FAILURE);

	philosophers = data.philosophers;
	
	return(0);
}