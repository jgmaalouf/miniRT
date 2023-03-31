/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:44:05 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 14:58:29 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

static t_quadratic	get_sphere_quadratics(const t_ray r, const t_sphere sp)
{
	t_quadratic	q;
	t_vec3		oc;

	q = (t_quadratic){0};
	oc = vec3_subtr(r.orig, sp.pos);
	q.a = vec3_length_squared(r.dir);
	q.half_b = vec3_dot(oc, r.dir);
	q.c = vec3_length_squared(oc) - sp.diameter * 0.5 * sp.diameter * 0.5;
	return (q);
}

static bool	hit_sphere(const t_ray r, const t_sphere sp, double t_max,
						double *t)
{
	t_quadratic	q;
	double		discriminant;
	double		sqrtd;

	q = get_sphere_quadratics(r, sp);
	discriminant = (q.half_b * q.half_b) - (q.a * q.c);
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	*t = (-q.half_b - sqrtd) / q.a;
	if (*t < T_MIN || t_max < *t)
	{
		*t = (-q.half_b + sqrtd) / q.a;
		if (*t < T_MIN || t_max < *t)
			return (false);
	}
	return (true);
}

bool	hit_sphere_record(const t_ray r, const t_sphere sp, double t_max,
							t_hit_record *temp_rec)
{
	if (hit_sphere(r, sp, t_max, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		temp_rec->normal = vec3_scale_div(
				vec3_subtr(temp_rec->p, sp.pos),
				sp.diameter * 0.5
				);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		temp_rec->color = vec3_scale_div(sp.rgb, 255);
		return (true);
	}
	return (false);
}
