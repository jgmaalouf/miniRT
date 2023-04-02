/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_random.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/02 17:37:08 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "utils.h"

t_vec3 vec3_random(double min, double max)
{
	return (vec3_constr(random_dbl(min, max), random_dbl(min, max), random_dbl(min, max)));
}

t_vec3	vec3_random_unit(void)
{
	return (vec3_unit(vec3_random(-1, 1)));
}

