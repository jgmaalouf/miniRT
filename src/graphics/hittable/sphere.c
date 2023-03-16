/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:44:05 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/16 19:57:25 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

bool	hit_sphere(const t_ray r, double t_max, t_sphere sp, double *root)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	sqrtd;

	oc = vec3_substr(r.orig, sp.pos);
	a = vec3_length_squared(r.dir);
	half_b = vec3_dot(oc, r.dir);
	c = vec3_length_squared(oc) - sp.diameter * 0.5 * sp.diameter * 0.5;
	*root = (half_b * half_b) - (a * c);
	if (*root < 0)
		return (false);
	sqrtd = sqrt(*root);
	*root = (-half_b - sqrtd) / a;
	if (*root < T_MIN || t_max < *root)
	{
		*root = (-half_b + sqrtd) / a;
		if (*root < T_MIN || t_max < *root)
			return (false);
	}
	return (true);
}

bool	hit_sphere_record(const t_ray r, double t_max, t_sphere sp,
							t_hit_record *temp_rec)
{
	if (hit_sphere(r, t_max, sp, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		temp_rec->normal = vec3_scale_div(
			vec3_substr(temp_rec->p, sp.pos),
			sp.diameter * 0.5
			);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}