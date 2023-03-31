/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:18 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 12:58:29 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
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

bool	hit_cylinder_plane_record(const t_ray r, const double t_max, const t_cylinder cy, t_hit_record *temp_rec)
{
	t_plane	help_pl;

	help_pl.orient = cy.orient;
	help_pl.pos = vec3_add(cy.pos, vec3_scale_mult(cy.orient, cy.diameter / 2.0));
	temp_rec->normal = vec3_unit(help_pl.orient);
	temp_rec->color = vec3_scale_div(cy.rgb, 255);
	if (hit_plane(r, t_max, help_pl, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		if (vec3_length(vec3_subtr(temp_rec->p, help_pl.pos)) <= cy.diameter / 2.0)
		{
			set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
			return (true);
		}
	}
	help_pl.pos = vec3_add(cy.pos, vec3_scale_mult(cy.orient, cy.diameter / -2.0));
	if (hit_plane(r, t_max, help_pl, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		if (vec3_length(vec3_subtr(temp_rec->p, help_pl.pos)) <= cy.diameter / 2.0)
		{
			set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
			return (true);
		}
	}
	return (false);
}
