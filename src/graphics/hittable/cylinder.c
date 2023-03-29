/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 06:57:00 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/29 13:30:53 by amorvai          ###   ########.fr       */
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

	rhs = vec3_subtr(cy.pos, r.orig);
	lhs[0] = vec3_constr(r.dir.e[0], -cy.orient.e[0], common_normal.e[0]);
	lhs[1] = vec3_constr(r.dir.e[1], -cy.orient.e[1], common_normal.e[1]);
	lhs[2] = vec3_constr(r.dir.e[2], -cy.orient.e[2], common_normal.e[2]);
	// if (lhs[0].e[0] != 0.0)
	// {
		ratio = lhs[1].e[0] / lhs[0].e[0];
		lhs[1] = vec3_subtr(lhs[1], vec3_scale_mult(lhs[0], ratio));
		rhs.e[1] = rhs.e[1] - rhs.e[0] * ratio;
		ratio = lhs[2].e[0] / lhs[0].e[0];
		lhs[2] = vec3_subtr(lhs[2], vec3_scale_mult(lhs[0], ratio));
		rhs.e[2] = rhs.e[2] - rhs.e[0] * ratio;
	// }
	// else
	// 	printf("issue1?\n");
	// if (lhs[1].e[2] != 0.0)
	// {
		ratio = lhs[2].e[2] / lhs[1].e[2];
		lhs[2] = vec3_subtr(lhs[2], vec3_scale_mult(lhs[1], ratio));
		rhs.e[2] = rhs.e[2] - rhs.e[1] * ratio;
	// }
	// else
		// printf("issue2?\n");
	// printf("%f =\t", rhs.e[2]);
	// print_vec3("lhs", lhs[2]);
	// if (lhs[2].e[1] != 0.0)
		return (rhs.e[2] / lhs[2].e[1]);
	// else 
	// {
		printf("ohoh?\n");
		return (0);
	// }
}

double	solve_distance_ray_cycenter(const t_vec3 common_normal, const t_ray r, const t_cylinder cy)
{
	double	d1;
	double	d2;

	d1 = vec3_dot(common_normal, r.orig);
	d2 = vec3_dot(common_normal, cy.pos);
	if (vec3_length(common_normal))
		return ((d2 - d1)/vec3_length(common_normal));
	return (0.0);
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
	// if (distance == 0.0)
		// printf("%f\n", distance);
		// distance = 0.1;
	common_normal = vec3_unit(common_normal);
	// print_vec3("common_normal", common_normal);
	common_common_normal = vec3_unit(vec3_cross(common_normal, cy.orient));
	// print_vec3("common_common_normal", common_common_normal);
	x = sqrt(pow(cy.diameter / 2.0, 2) - pow(distance, 2));
	common_normal = vec3_scale_mult(common_normal, distance);
	temp_rec->normal = vec3_unit(vec3_add(common_normal, vec3_scale_mult(common_common_normal, x)));
	// print_vec3("temp_rec->normal", temp_rec->normal);
	t_cy = solve_cylinder_t(temp_rec->normal, r, cy);
	if (t_cy > cy.height / 2 || t_cy < cy.height / -2)
	{
		temp_rec->normal = vec3_unit(vec3_add(common_normal, vec3_scale_mult(common_common_normal, -x)));
		t_cy = solve_cylinder_t(temp_rec->normal, r, cy);
		if (t_cy > cy.height / 2 || t_cy < cy.height / -2)
			return (false);
	}
	temp_rec->t = solve_ray_t(r, cy, t_cy, t_max);
	if (temp_rec->t < T_MIN || t_max < temp_rec->t)
		return (false);
	return (true);
}

// bool	hit_cylinder_record(const t_ray r, const double t_max, const t_cylinder cy,
// 							t_hit_record *temp_rec)
// {
// 	if (hit_cylinder(r, t_max, cy, temp_rec))
// 	{
// 		temp_rec->p = ray_at(r, temp_rec->t);
// 		temp_rec->color = vec3_scale_div(cy.rgb, 255);
// 		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
// 		return (true);
// 	}
// 	return (false);
// }

// t_point3 ft_find_edges(t_cylinder cylinder, t_ray ray,
// 							t_point3 inter_point)
// {
// 	double a;

// 	ft_get_normal(ray, cylinder.pos, &inter_point);
// 	if (get_norm(sub(inter_point.coord, cylinder.pos)) > cylinder.height)
// 		return (inter_point);
// 	a = dot(cylinder.rot, sub(inter_point.coord, cylinder.pos));
// 	inter_point.normal = normalize(sub(inter_point.coord, add(cylinder.pos, ft_scale(cylinder.rot, a))));
// 	inter_point.hit = TRUE;
// 	return (inter_point);
// }

bool	ft_cylinder_collision(const t_ray r, const double t_max, const t_cylinder cy, t_hit_record *temp_rec)
{
	double	inter_point[2];
	double	delta[4];
	t_ray	new_ray;
	t_vec3	c_to_o;

	// inter_point.hit = FALSE;
	// inter_point.id = id;
	new_ray.orig = r.orig;
	// cy.orient = vec3_unit(cy.orient);
	new_ray.dir = vec3_cross(r.dir, cy.orient);
	c_to_o = vec3_subtr(r.orig, cy.pos);
	delta[0] = vec3_dot(new_ray.dir, new_ray.dir);
	delta[1] = 2 * vec3_dot(new_ray.dir, vec3_cross(c_to_o, cy.orient));
	delta[2] = vec3_dot(vec3_cross(c_to_o, cy.orient), vec3_cross(c_to_o, cy.orient)) - pow(cy.diameter / 2, 2);
	delta[3] = pow(delta[1], 2) - 4 * delta[2] * delta[0];
	if (delta[3] < 0)
		return (false);
	inter_point[0] = (-delta[1] - sqrt(delta[3])) / (2 * delta[0]);
	inter_point[1] = (-delta[1] + sqrt(delta[3])) / (2 * delta[0]);
	if (inter_point[0] > inter_point[1])
		temp_rec->t = inter_point[1];
	else
		temp_rec->t = inter_point[0];
	double	f = r.orig.e[1] + temp_rec->t * r.dir.e[1];
	if (f <= cy.pos.e[1] - cy.height / 2.0 || f >= cy.pos.e[1] + cy.height / 2.0)
		return (false);

	//try
	// t_vec3	g = ray_at(r, temp_rec->t);
	// if (g <= vec3_sub(cy.pos, vec3_scale_mult(cy.orient, cy.height / 2.0)) || g >= vec3_add(cy.pos, vec3_scale_mult(cy.orient, cy.height / 2.0)))
		// return (false);
	
	if (temp_rec->t < T_MIN || t_max < temp_rec->t)
		return (false);
	return (true);
}

bool	hit_cylinder_record(const t_ray r, const double t_max, const t_cylinder cy,
							t_hit_record *temp_rec)
{
	if (ft_cylinder_collision(r, t_max, cy, temp_rec))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		temp_rec->normal = vec3_unit(vec3_constr(temp_rec->p.e[0] - cy.pos.e[0], 0, temp_rec->p.e[2] - cy.pos.e[2]));
		temp_rec->color = vec3_scale_div(cy.rgb, 255);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}
