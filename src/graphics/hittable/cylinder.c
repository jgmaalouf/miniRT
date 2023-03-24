/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 06:57:00 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/24 13:27:13 by amorvai          ###   ########.fr       */
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

bool	hit_cylinder(const t_ray r, const double t_max, const t_cylinder cy,
						t_hit_record *temp_rec)
{
	t_vec3	common_normal;
	t_vec3	common_common_normal;
	double	d1;
	double	d2;
	double	distance;

	common_normal = vec3_cross(r.dir, cy.orient);
	d1 = vec3_dot(common_normal, r.orig);
	d2 = vec3_dot(common_normal, cy.pos);
	distance = (d1 - d2)/vec3_length(common_normal);
	// printf("cy.diameter: %f\n", cy.diameter);
	if (distance > cy.diameter/2.0 || distance < cy.diameter/-2.0)
	{
		return (false);
	}
	common_normal = vec3_unit(common_normal);
	common_common_normal = vec3_unit(vec3_cross(common_normal, cy.orient));
	double x = sqrt(pow(cy.diameter / 2.0, 2) - pow(distance, 2));
	// if (distance < 0)
		// x = x * -1.0;
	temp_rec->normal = vec3_unit(vec3_add(vec3_scale_mult(common_normal, distance), vec3_scale_mult(common_common_normal, x)));
	// print_vec3("cylinder normal", temp_rec->normal);
	return (true);
	if (temp_rec->t < T_MIN || t_max < temp_rec->t)
	{
		return (false);
	}
}

bool	hit_cylinder_record(const t_ray r, const double t_max, const t_cylinder cy,
							t_hit_record *temp_rec)
{
	if (hit_cylinder(r, t_max, cy, temp_rec))
	{
		temp_rec->color = vec3_constr(1,1,1);
		// temp_rec->p = ray_at(r, temp_rec->t);
		// temp_rec->normal = 
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}
