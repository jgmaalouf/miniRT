/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:18 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 19:01:50 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

bool	hit_cone_plane_record(const t_ray r, const t_cone co,
									double *t_max, t_hit_record *temp_rec)
{
	bool	hit;
	t_plane	help_pl;
	double	radius;

	hit = false;
	help_pl.orient = co.orient;
	help_pl.pos = vec3_add(co.pos, vec3_scale_mult(co.orient, co.diameter));
	radius = tan(co.angle * M_PI / 180) * co.diameter;
	if (hit_plane(r, help_pl, *t_max, &temp_rec->t)
		&& plane_in_range(r, radius, help_pl, temp_rec))
	{
		*t_max = temp_rec->t;
		temp_rec->color = vec3_scale_div(co.rgb, 255);
		hit = true;
	}
	help_pl.pos = vec3_add(co.pos, vec3_scale_mult(co.orient, co.height));
	radius = tan(co.angle * M_PI / 180) * co.height;
	if (hit_plane(r, help_pl, *t_max, &temp_rec->t)
		&& plane_in_range(r, radius, help_pl, temp_rec))
	{
		*t_max = temp_rec->t;
		temp_rec->color = vec3_scale_div(co.rgb, 255);
		hit = true;
	}
	return (hit);
}
