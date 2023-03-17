/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_random.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:12:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/14 17:41:01 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>

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

t_vec3	vec3_random_in_unit_sp(void)
{
	t_vec3	p;

	p = vec3_random(-1, 1);
	while (vec3_length_squared(p) >= 1)
		p = vec3_random(-1, 1);
	return (p);
}
