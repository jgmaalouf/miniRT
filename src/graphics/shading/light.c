/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:21:04 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/29 19:13:37 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"
#include "intersection.h"
#include "utils.h"

/*
	Determines if the ray intersects an object and sets
	the visibility boolean accordingly
*/
double	shadow_hit(t_ray shadow_ray, t_hittable objects,
			t_hit_record hitpoint, t_vec3 light)
{
	t_hit_record	shadow_rec;
	double			visiblity;

	shadow_rec = (t_hit_record){0};
	visiblity = !world_hit(shadow_ray, &shadow_rec, objects);
	if (visiblity == 0)
	{
		if (vec3_length(light)
			< vec3_length(vec3_subtr(hitpoint.p, shadow_rec.p)))
			visiblity = 1;
	}
	return (visiblity);
}

/*
	Determines how the light will look like on the objects using the
	attenuation (which is a fancy word for how bright the point is).
	We get the attenuation by finding the value of cosine of
	the angle between the hitpoint normal and the light direction,
	which we get by dividing the dot product of the two vectors with
	the length of the two vectors multiplied (since the two vectors
	are normalize we can omit the division).
	Finally, we determine if the point is in the shadow by setting
	the visible boolean. Effectively turning the color off or on when
	we multiply the point with the boolean.
*/
t_color	get_light_shade(const t_scene *scene, const t_hit_record hitpoint)
{
	t_vec3			light_vec;
	t_ray			shadow_ray;
	double			visiblity;
	double			attenuation;
	t_color			light_color;

	light_vec = vec3_subtr(scene->light.pos, hitpoint.p);
	shadow_ray = ray_constr(hitpoint.p, vec3_unit(light_vec));
	visiblity = shadow_hit(shadow_ray, scene->hittable, hitpoint, light_vec);
	attenuation = fmax(vec3_dot(vec3_unit(light_vec), hitpoint.normal), 0.0);
	light_color = vec3_scale_mult(scene->light.energy, attenuation);
	return (vec3_scale_mult(light_color, visiblity));
	return (light_color);
}
