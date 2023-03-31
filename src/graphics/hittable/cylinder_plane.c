/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:18 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 18:44:48 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

bool	hit_cylinder_plane_record(const t_ray r, const t_cylinder cy,
									double *t_max, t_hit_record *temp_rec)
{
	bool	hit;
	t_plane	help_pl;
	t_vec3	half_height;

	hit = false;
	help_pl.orient = cy.orient;
	half_height = vec3_scale_mult(cy.orient, cy.height / 2.0);
	help_pl.pos = vec3_add(cy.pos, half_height);
	if (hit_plane(r, help_pl, *t_max, &temp_rec->t)
		&& plane_in_range(r, cy.diameter / 2.0, help_pl, temp_rec))
	{
		*t_max = temp_rec->t;
		temp_rec->color = vec3_scale_div(cy.rgb, 255);
		hit = true;
	}
	help_pl.pos = vec3_subtr(cy.pos, half_height);
	if (hit_plane(r, help_pl, *t_max, &temp_rec->t)
		&& plane_in_range(r, cy.diameter / 2.0, help_pl, temp_rec))
	{
		*t_max = temp_rec->t;
		temp_rec->color = vec3_scale_div(cy.rgb, 255);
		hit = true;
	}
	return (hit);
}
