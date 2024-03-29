/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:56:06 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 14:58:42 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h> // printf

bool	hit_plane(const t_ray r, const t_plane pl, double t_max, double *t)
{
	double	dir_xnorm;
	double	pos_min_orig__xnorm;

	dir_xnorm = vec3_dot(r.dir, pl.orient);
	pos_min_orig__xnorm = vec3_dot(pl.orient, vec3_subtr(pl.pos, r.orig));
	*t = pos_min_orig__xnorm / dir_xnorm;
	if (*t < T_MIN || t_max < *t)
		return (false);
	return (true);
}

bool	hit_plane_record(const t_ray r, const t_plane pl, double t_max,
							t_hit_record *temp_rec)
{
	if (hit_plane(r, pl, t_max, &temp_rec->t))
	{
		temp_rec->p = ray_at(r, temp_rec->t);
		temp_rec->normal = pl.orient;
		set_face_normal(r, &temp_rec->normal, &temp_rec->front_face);
		temp_rec->color = vec3_scale_div(pl.rgb, 255);
		return (true);
	}
	return (false);
}
