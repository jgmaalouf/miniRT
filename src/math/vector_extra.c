/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/28 15:25:54 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>
#include "utils.h"

// TODO: Probably create a generator myself

static double	random_dbl(double min, double max)
{
	double	random;

	random = (max - min) * arc4random_uniform(RAND_MAX) / (double)RAND_MAX + min;
	return (random);
}

t_vec3 vec3_random(double min, double max)
{
	return (vec3_constr(random_dbl(min, max), random_dbl(min, max), random_dbl(min, max)));
}

t_vec3	vec3_random_unit(void)
{
	return (vec3_unit(vec3_random(-1, 1)));
}

t_vec3	vec3_clamp(t_vec3 vec, double min, double max)
{
	vec.e[0] = clamp(vec.e[0], min, max);
	vec.e[1] = clamp(vec.e[1], min, max);
	vec.e[2] = clamp(vec.e[2], min, max);
	return (vec);
}
