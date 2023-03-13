/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:39:48 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/10 20:32:26 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_constr(const t_point3 origin, const t_vec3 direction)
{
	t_ray	ray;

	ray.orig = origin;
	ray.dir = direction;
	return (ray);
}

t_point3	ray_at(const t_ray ray, const double t)
{
	return (
		vec3_add(
			ray.orig,
			vec3_scale_mult(ray.dir, t)
		)
	);
}
