/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:36:01 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 14:58:55 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

static t_quadratic	get_cylinder_quadratics(const t_ray r, const t_cylinder cy)
{
	t_quadratic	q;
	t_vec3		oc;
	double		dot_rdir_cyorient;

	q = (t_quadratic){0};
	oc = vec3_subtr(r.orig, cy.pos);
	dot_rdir_cyorient = vec3_dot(r.dir, cy.orient);
	q.dot_oc_cyorient = vec3_dot(oc, cy.orient);
	q.a = vec3_length_squared(r.dir)
		- pow(dot_rdir_cyorient, 2);
	q.half_b = vec3_dot(r.dir, oc)
		- dot_rdir_cyorient * q.dot_oc_cyorient;
	q.c = vec3_length_squared(oc)
		- pow(q.dot_oc_cyorient, 2) - pow(cy.diameter / 2.0, 2);
	return (q);
}

static bool	cylinder_in_range(const t_ray r, const t_cylinder cy,
								const double t_max, t_quadratic	*q)
{
	q->m = q->dot_oc_cyorient
		+ vec3_dot(
			r.dir,
			vec3_scale_mult(
				cy.orient,
				q->t
				)
			);
	if (q->m > cy.height / 2.0 || q->m < cy.height / -2.0
		|| q->t < T_MIN || q->t > t_max)
		return (false);
	return (true);
}

static bool	hit_cylinder(const t_ray r, const t_cylinder cy, const double t_max,
							t_hit_record *temp_rec)
{
	t_quadratic	q;
	double		discriminant;
	double		sqrtd;

	q = get_cylinder_quadratics(r, cy);
	discriminant = (q.half_b * q.half_b) - (q.a * q.c);
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	q.t = (-q.half_b - sqrtd) / q.a;
	if (!cylinder_in_range(r, cy, t_max, &q))
	{
		q.t = (-q.half_b + sqrtd) / q.a;
		if (!cylinder_in_range(r, cy, t_max, &q))
			return (false);
	}
	temp_rec->t = q.t;
	temp_rec->p = ray_at(r, q.t);
	temp_rec->normal = vec3_unit(
			vec3_subtr(
				temp_rec->p,
				vec3_add(
					cy.pos,
					vec3_scale_mult(cy.orient, q.m))));
	return (true);
}

bool	hit_cylinder_record(const t_ray r, const t_cylinder cy,
								const double t_max, t_hit_record *temp_rec)
{
	if (hit_cylinder(r, cy, t_max, temp_rec))
	{
		temp_rec->color = vec3_scale_div(cy.rgb, 255);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}
