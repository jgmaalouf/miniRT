/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 06:57:00 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/20 10:10:10 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

bool	hit_cylinder(const t_ray r, double t_max, t_cylinder cy, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	sqrtd;

	// oc = vec3_subtr(r.orig, cy.pos);
	
	// a = vec3_length_squared(r.dir);
	if (*t < 0)
		return (false);
	// sqrtd = sqrt(*root);
	// *t = (-half_b - sqrtd) / a;
	if (*t < T_MIN || t_max < *t)
	{
		// *t = (-half_b + sqrtd) / a;
		// if (*t < T_MIN || t_max < *t)
			return (false);
	}
	return (true);
}

bool	hit_cylinder_record(const t_ray r, double t_max, t_cylinder cy,
							t_hit_record *temp_rec)
{
	if (hit_cylinder(r, t_max, cy, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		// temp_rec->normal = vec3_scale_div(
		// 	vec3_subtr(temp_rec->p, cy.pos),
		// 	cy.diameter * 0.5
		// 	);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}
