/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 06:57:00 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/26 20:00:38 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

double	solve_ray_t(const t_ray r, const t_cylinder cy, const double t_cy, const double t_max)
{
	t_sphere	help_sphere;
	double		t_new;

	help_sphere.pos = vec3_add(cy.pos, vec3_scale_mult(cy.orient, t_cy));
	help_sphere.diameter = cy.diameter;
	hit_sphere(r, t_max, help_sphere, &t_new);
	return (t_new);
}

double	solve_cylinder_t(const t_vec3 common_normal, const t_ray r, const t_cylinder cy)
{
	t_vec3	rhs;
	t_vec3	lhs[3];
	double	ratio;

	rhs = vec3_substr(cy.pos, r.orig);
	lhs[0] = vec3_constr(r.dir.e[0], -cy.orient.e[0], common_normal.e[0]);
	lhs[1] = vec3_constr(r.dir.e[1], -cy.orient.e[1], common_normal.e[1]);
	lhs[2] = vec3_constr(r.dir.e[2], -cy.orient.e[2], common_normal.e[2]);
	ratio = lhs[1].e[0] / lhs[0].e[0];
	lhs[1] = vec3_substr(lhs[1], vec3_scale_mult(lhs[0], ratio));
	rhs.e[1] = rhs.e[1] - rhs.e[0] * ratio;
	ratio = lhs[2].e[0] / lhs[0].e[0];
	lhs[2] = vec3_substr(lhs[2], vec3_scale_mult(lhs[0], ratio));
	rhs.e[2] = rhs.e[2] - rhs.e[0] * ratio;
	ratio = lhs[2].e[2] / lhs[1].e[2];
	lhs[2] = vec3_substr(lhs[2], vec3_scale_mult(lhs[1], ratio));
	rhs.e[2] = rhs.e[2] - rhs.e[1] * ratio;
	// printf("%f =\t", rhs.e[2]);
	// print_vec3("lhs", lhs[2]);
	return (rhs.e[2] / lhs[2].e[1]);
}

double	solve_distance_ray_cycenter(const t_vec3 common_normal, const t_ray r, const t_cylinder cy)
{
	double	d1;
	double	d2;

	d1 = vec3_dot(common_normal, r.orig);
	d2 = vec3_dot(common_normal, cy.pos);
	return ((d2 - d1)/vec3_length(common_normal));
}

bool	hit_cylinder(const t_ray r, const double t_max, const t_cylinder cy, t_hit_record *temp_rec)
{
	t_vec3	common_common_normal;
	t_vec3	common_normal;
	double	distance;
	double	t_cy;
	double	x;

	common_normal = vec3_cross(cy.orient, r.dir);
	distance = solve_distance_ray_cycenter(common_normal, r, cy);
	if (distance > cy.diameter / 2.0 || distance < cy.diameter / -2.0)
		return (false);
	common_normal = vec3_unit(common_normal);
	common_common_normal = vec3_unit(vec3_cross(common_normal, cy.orient));
	x = sqrt(pow(cy.diameter / 2.0, 2) - pow(distance, 2));
	temp_rec->normal = vec3_unit(vec3_add(vec3_scale_mult(common_normal, distance), vec3_scale_mult(common_common_normal, x)));
	t_cy = solve_cylinder_t(temp_rec->normal, r, cy);
	if (t_cy > cy.height / 2 || t_cy < cy.height / -2)
		return (false);
	temp_rec->t = solve_ray_t(r, cy, t_cy, t_max);
	if (temp_rec->t < T_MIN || t_max < temp_rec->t)
		return (false);
	temp_rec->p = ray_at(r, temp_rec->t);
	return (true);
}

bool	hit_cylinder_record(const t_ray r, const double t_max, const t_cylinder cy,
							t_hit_record *temp_rec)
{
	if (hit_cylinder(r, t_max, cy, temp_rec))
	{
		temp_rec->color = vec3_scale_div(cy.rgb, 255);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}
