/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:31:17 by cmakario          #+#    #+#             */
/*   Updated: 2024/08/07 17:01:40 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

/* -------------------------- utils.c ------------------------- */

size_t	ft_strlen(const char *s);
int		print_error(char *msg);
int		is_valid_number(char *str);
bool	input_is_valid(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_isdigit(int a);


#endif // PHILO_H