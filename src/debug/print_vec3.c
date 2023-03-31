/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:00:27 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 18:02:25 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	print_vec3(char *name, t_vec3 vec)
{
	printf("vector [%s]:\t[%f][%f][%f]\n", name, vec.e[0], vec.e[1], vec.e[2]);
}
