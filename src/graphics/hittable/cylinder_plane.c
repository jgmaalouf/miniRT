/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:18 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 01:14:50 by amorvai          ###   ########.fr       */
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

/* to see normal-colors of the sides of any hittable

after		if (world_hit())	in ray_calc.c
insert:
				return (vec3_scale_mult(vec3_add(hit_rec.normal, vec3_constr(1.0, 1.0, 1.0)), 0.5));
*/

bool	hit_cylinder_plane_record_1(const t_ray r, const double t_max, const t_cylinder cy, t_hit_record *temp_rec)
{
	t_plane	help_pl;
	t_vec3	half_height;

	help_pl.orient = cy.orient;
	half_height = vec3_scale_mult(cy.orient, cy.height / 2.0);
	help_pl.pos = vec3_add(cy.pos, half_height);
	if (hit_plane(r, t_max, help_pl, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		if (vec3_length(vec3_subtr(temp_rec->p, help_pl.pos)) <= cy.diameter / 2.0)
		{
			temp_rec->normal = vec3_unit(help_pl.orient);
			temp_rec->color = vec3_scale_div(cy.rgb, 255);
			set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
			return (true);
		}
	}
	return (false);
}

bool	hit_cylinder_plane_record_2(const t_ray r, const double t_max, const t_cylinder cy, t_hit_record *temp_rec)
{
	t_plane	help_pl;
	t_vec3	half_height;

	help_pl.orient = cy.orient;
	half_height = vec3_scale_mult(cy.orient, cy.height / 2.0);
	help_pl.pos = vec3_subtr(cy.pos, half_height);
	if (hit_plane(r, t_max, help_pl, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		if (vec3_length(vec3_subtr(temp_rec->p, help_pl.pos)) <= cy.diameter / 2.0)
		{
			temp_rec->normal = vec3_unit(help_pl.orient);
			temp_rec->color = vec3_scale_div(cy.rgb, 255);
			set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
			return (true);
		}
	}
	return (false);
}
