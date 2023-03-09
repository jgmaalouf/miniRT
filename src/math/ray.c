/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:39:48 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/09 11:44:03 by amorvai          ###   ########.fr       */
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

t_point3	ray_origin(const t_ray ray)
{
	return (ray.orig);
}

t_vec3		ray_direction(const t_ray ray)
{
	return (ray.dir);
}

t_point3	ray_at(const t_ray ray, const double t)
{
	return ((const t_point3)vec3_add(
		(const t_vec3)ray.orig,
		vec3_scale_mult(ray.dir, t)
	));
}
