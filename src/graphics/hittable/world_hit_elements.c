/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_hit_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:02:26 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 19:02:51 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <stdbool.h>
#include <stdlib.h> // size_t
#include <stdio.h> // size_t

bool	world_hit_sphere(const t_ray r, const t_hittable objs,
							t_hit_record *rec, double *closest_t)
{
	bool			hit;
	t_hit_record	temp_rec;
	size_t			i;

	hit = false;
	temp_rec = (t_hit_record){0};
	i = 0;
	while (i < objs.sp_count)
	{
		if (hit_sphere_record(r, objs.spheres[i], *closest_t, &temp_rec))
		{
			hit = true;
			*closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit);
}

bool	world_hit_plane(const t_ray r, const t_hittable objs,
							t_hit_record *rec, double *closest_t)
{
	bool			hit;
	t_hit_record	temp_rec;
	size_t			i;

	hit = false;
	temp_rec = (t_hit_record){0};
	i = 0;
	while (i < objs.pl_count)
	{
		if (hit_plane_record(r, objs.planes[i], *closest_t, &temp_rec))
		{
			hit = true;
			*closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit);
}

bool	world_hit_cylinder(const t_ray r, const t_hittable objs,
							t_hit_record *rec, double *closest_t)
{
	bool			hit;
	t_hit_record	temp_rec;
	size_t			i;

	hit = false;
	temp_rec = (t_hit_record){0};
	i = 0;
	while (i < objs.cy_count)
	{
		if (hit_cylinder_record(r, objs.cylinders[i], *closest_t, &temp_rec))
		{
			hit = true;
			*closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		if (hit_cylinder_plane_record(r, objs.cylinders[i], closest_t,
				&temp_rec))
		{
			hit = true;
			*closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit);
}

bool	world_hit_cone(const t_ray r, const t_hittable objs,
							t_hit_record *rec, double *closest_t)
{
	bool			hit;
	t_hit_record	temp_rec;
	size_t			i;

	hit = false;
	temp_rec = (t_hit_record){0};
	i = 0;
	while (i < objs.co_count)
	{
		if (hit_cone_record(r, objs.cones[i], *closest_t, &temp_rec))
		{
			hit = true;
			*closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		if (hit_cone_plane_record(r, objs.cones[i], closest_t,
				&temp_rec))
		{
			hit = true;
			*closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit);
}
