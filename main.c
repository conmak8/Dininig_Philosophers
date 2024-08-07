/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:35:27 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 17:36:48 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim_data data;
	// handle arguments num and validation
	if(!input_is_valid(argc, ++argv))
		return(EXIT_FAILURE);
	// initialize data
	if(!initilize_data(argc, argv, &data));
		return(EXIT_FAILURE);
	
	
	
	
	return(0);
	
}