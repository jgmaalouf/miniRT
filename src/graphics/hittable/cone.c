/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:36:01 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 18:57:15 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

static t_quadratic	get_cone_quadratics(const t_ray r, const t_cone co,
											const double k_squared_plus_one)
{
	t_quadratic	q;
	t_vec3		oc;
	double		dot_rdir_cyorient;

	q = (t_quadratic){0};
	oc = vec3_subtr(r.orig, co.pos);
	dot_rdir_cyorient = vec3_dot(r.dir, co.orient);
	q.dot_oc_cyorient = vec3_dot(oc, co.orient);
	q.a = vec3_length_squared(r.dir)
		- k_squared_plus_one * pow(dot_rdir_cyorient, 2);
	q.half_b = vec3_dot(r.dir, oc)
		- k_squared_plus_one * dot_rdir_cyorient * q.dot_oc_cyorient;
	q.c = vec3_length_squared(oc)
		- k_squared_plus_one * pow(q.dot_oc_cyorient, 2);
	return (q);
}

static bool	cone_in_range(const t_ray r, const t_cone co, const double t_max,
							t_quadratic *q)
{
	q->m = q->dot_oc_cyorient
		+ vec3_dot(
			r.dir,
			vec3_scale_mult(
				co.orient,
				q->t
				)
			);
	if (q->m < co.diameter || q->m > co.height || q->t < T_MIN || q->t > t_max)
		return (false);
	return (true);
}

static bool	hit_cone(const t_ray r, const t_cone co, const double t_max,
							t_hit_record *temp_rec)
{
	t_quadratic	q;
	double		discriminant;
	double		sqrtd;
	double		k_squared_plus_one;

	k_squared_plus_one = pow(tan(co.angle * M_PI / 180), 2) + 1.0;
	q = get_cone_quadratics(r, co, k_squared_plus_one);
	discriminant = (q.half_b * q.half_b) - (q.a * q.c);
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	q.t = (-q.half_b - sqrtd) / q.a;
	if (!cone_in_range(r, co, t_max, &q))
	{
		q.t = (-q.half_b + sqrtd) / q.a;
		if (!cone_in_range(r, co, t_max, &q))
			return (false);
	}
	temp_rec->t = q.t;
	temp_rec->p = ray_at(r, q.t);
	temp_rec->normal = vec3_unit(vec3_subtr(temp_rec->p, vec3_add(co.pos,
					vec3_scale_mult(co.orient, q.m * k_squared_plus_one))));
	return (true);
}

bool	hit_cone_record(const t_ray r, const t_cone co,
								const double t_max, t_hit_record *temp_rec)
{
	if (hit_cone(r, co, t_max, temp_rec))
	{
		temp_rec->color = vec3_scale_div(co.rgb, 255);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}
