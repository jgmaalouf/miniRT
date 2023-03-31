/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:57:13 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 19:02:48 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "scene.h"
#include "ray.h"
#include "vector.h"

#include <stdbool.h>
#include <stdlib.h> // size_t
#include <stdio.h> // size_t

bool	world_hit(const t_ray r, t_hit_record *rec, const t_hittable objects)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	size_t			i;
	size_t			num_hittable;

	num_hittable = sizeof(g_world_hittable) / sizeof(g_world_hittable[0]);
	i = 0;
	temp_rec = (t_hit_record){0};
	closest_so_far = T_MAX;
	hit_anything = false;
	while (i < num_hittable)
	{
		if (g_world_hittable[i](r, objects, &temp_rec, &closest_so_far))
		{
			hit_anything = true;
			*rec = temp_rec;
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
