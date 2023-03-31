/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:18 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 14:59:16 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

static bool	cylinder_plane_in_range(const t_ray r, const t_cylinder cy,
								const t_plane help_pl, t_hit_record *temp_rec)
{
	temp_rec->p = ray_at(r, temp_rec->t);
	if (vec3_length(vec3_subtr(temp_rec->p, help_pl.pos)) <= cy.diameter / 2.0)
	{
		temp_rec->normal = vec3_unit(help_pl.orient);
		temp_rec->color = vec3_scale_div(cy.rgb, 255);
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		return (true);
	}
	return (false);
}

bool	hit_cylinder_plane_record(const t_ray r, const t_cylinder cy,
									const double t_max, t_hit_record *temp_rec)
{
	t_plane	help_pl;
	t_vec3	half_height;

	help_pl.orient = cy.orient;
	half_height = vec3_scale_mult(cy.orient, cy.height / 2.0);
	help_pl.pos = vec3_add(cy.pos, half_height);
	if (hit_plane(r, help_pl, t_max, &temp_rec->t)
		&& cylinder_plane_in_range(r, cy, help_pl, temp_rec))
		return (true);
	help_pl.pos = vec3_subtr(cy.pos, half_height);
	if (hit_plane(r, help_pl, t_max, &temp_rec->t)
		&& cylinder_plane_in_range(r, cy, help_pl, temp_rec))
		return (true);
	return (false);
}
