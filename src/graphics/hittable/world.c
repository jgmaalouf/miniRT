/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:57:13 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/27 00:26:07 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <stdbool.h>

bool	world_hit(const t_ray r, t_hit_record *rec, const t_hittable objects)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	int				i;

	temp_rec = (t_hit_record){0};
	hit_anything = false;
	closest_so_far = T_MAX;
	i = 0;
	while (i < objects.sp_count)
	{
		if (hit_sphere_record(r, closest_so_far, objects.spheres[i], &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	i = 0;
	while (i < objects.pl_count)
	{
		if (hit_plane_record(r, closest_so_far, objects.planes[i], &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	i = 0;
	while (i < objects.cy_count)
	{
		if (hit_cylinder_record(r, closest_so_far, objects.cylinders[i], &temp_rec))
		{
			*rec = temp_rec;
			hit_anything = true;
			closest_so_far = temp_rec.t;
			// if (hit_cylinder_plane_record(r, closest_so_far, objects.cylinders[i], &temp_rec))
			// {
			// 	*rec = temp_rec;
			// 	hit_anything = true;
			// 	closest_so_far = temp_rec.t;
			// } // to be worked on
		}
		i++;
	}
	return (hit_anything);
}

void	set_face_normal(const t_ray r, t_vec3 *outward_normal, bool *front_face)
{
	if (vec3_dot(r.dir, *outward_normal) < 0)
		*front_face = true;
	else
	{
		*front_face = false;
		*outward_normal = vec3_scale_mult(*outward_normal, -1);
	}
}
