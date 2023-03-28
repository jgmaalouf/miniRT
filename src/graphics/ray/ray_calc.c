/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/28 01:50:53 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "utils.h"

#include "debug.h" // print_vec3
#include <stdio.h> // printf
#include <stdlib.h> // uint_t

/* 
static t_vec3	random_dir(const t_hit_record hit_rec)
{
	return(vec3_unit(vec3_add(hit_rec.normal, vec3_random_unit())));
}
// YOU ARE STOOPID THIS IS THE SOMETHING ELSE YOU SIMPLETON NOT LUMINOSITY
t_color	luminosity(t_scene *scene, const t_hit_record hit_rec, int depth)
{
	t_color	luminance;

	luminance = vec3_scale_mult(ray_color(ray_constr(hit_rec.p, random_dir(hit_rec)), scene, depth - 1), 0.5);
	if (luminance.e[0] == 0 && luminance.e[1] == 0 && luminance.e[2] == 0)
		luminance = vec3_constr(1, 1, 1);
	return (luminance);
}
*/

double	shadow_hit(t_ray shadow_ray, t_hittable objects, t_hit_record hitpoint, t_vec3 light)
{
	t_hit_record	shadow_rec;
	double			visiblity;

	shadow_rec = (t_hit_record){0};
	visiblity = !world_hit(shadow_ray, &shadow_rec, objects);
	if (visiblity == 0)
	{
		if (vec3_length(light) < vec3_length(vec3_subtr(hitpoint.p, shadow_rec.p)))
			visiblity = 1;
	}
	return (visiblity);
}

t_color	mix_lights(t_amb_light amb_light, t_light light) // We should consider doing a function that approximates zero because of the floating point errors we might get.
{
	if (amb_light.ratio == 0 && light.ratio == 0)
		return (vec3_constr(0, 0, 0));
	if (amb_light.ratio == 0)
		return (light.energy);
	if (light.ratio == 0)
		return (amb_light.energy);
	return (vec3_mult(amb_light.energy, light.energy));
}

/*
	Determines the shade of the objects using the attenuation (which is a fancy word for how bright the point is).
	We get the attenuation by finding the value of cosine the angle between the normal and the light direction.
	Which we get by dividing the dot product of the two vectors with the length of the two vectors multiplied.
	Finally, we determine if the point is in the shadow by setting the visible boolean. Effectively turning the 
	color off or on when we multiply it with the boolean.
*/
// color = vec3_scale_mult(vec3_add(vec3_scale_mult(hitpoint.color, attenuation), vec3_scale_mult(hitpoint.color, scene->amb_light.ratio)), 0.5);
t_color	shade(const t_hit_record hitpoint, const t_scene *scene)
{
	t_color			light_color;
	t_vec3			light_vec;
	t_vec3			light_dir;
	double			attenuation;
	t_ray			shadow_ray;
	double			visiblity;

	light_vec = vec3_subtr(scene->light.pos, hitpoint.p);
 	light_dir = vec3_scale_mult(vec3_unit(light_vec), scene->light.ratio);
	// To get the cos(a) we divide the dot product with the length of the light direction multiplied by the length of the normal, but since these two values are 1 since they are normalized, we can omit them.
	attenuation = clamp_min(vec3_dot(light_dir, hitpoint.normal), 0.0);
	shadow_ray = ray_constr(hitpoint.p, light_dir);
	visiblity = shadow_hit(shadow_ray, scene->hittable, hitpoint, light_vec);
	light_color = mix_lights(scene->amb_light, scene->light);
	if (scene->light.ratio != 0)
		light_color = vec3_scale_mult(light_color, attenuation);
	return (vec3_scale_mult(vec3_mult(hitpoint.color, light_color), visiblity));
}

/*
	Checks if the ray hits any objects. If that's the case we shade accordingly.
	Otherwise, we return black.
*/
t_color	ray_color(const t_ray r, t_scene *scene)
{
	t_color			color;
	t_hit_record	hit_rec;

	hit_rec = (t_hit_record){0};
	color = (t_color){0};
	if (world_hit(r, &hit_rec, scene->hittable))
		color = shade(hit_rec, scene);
	return (color);
}

/*
	Converts the pixel into something that the camera can shoot rays through in 3 steps.
		1. Convert from pixels to NDC space (Normalized Device Coordinates) range (0, 1).
		2. Convert from NDC space to screen space range (-1, 1).
		3. Convert from screen space to camera space.
*/
void pixel_to_world(t_scene *scene, double *x, double *y)
{
	double px_ndc_x;
	double px_ndc_y;
	double px_screen_x;
	double px_screen_y;

	if (SPP > 1)
	{
		px_ndc_x = (*x + random_double_in(0, 1)) / scene->image.width;
		px_ndc_y = (*y + random_double_in(0, 1)) / scene->image.height;
	}
	else
	{
		px_ndc_x = (*x + 0.5) / scene->image.width;
		px_ndc_y = (*y + 0.5) / scene->image.height;
	}
	px_screen_x = 2 * px_ndc_x - 1;
	px_screen_y = 1 - 2 * px_ndc_y;
	*x  = px_screen_x * scene->image.ratio * tan(((double)scene->camera.fov * (M_PI / 180.0)) / 2.0);
	*y  = px_screen_y * tan(((double)scene->camera.fov * (M_PI / 180.0)) / 2.0);
}

/*
	Sends a ray to the scene through the given pixels.
*/
static t_ray	get_next_ray(t_scene *scene, double x, double y)
{
	t_ray	ray;
	t_vec3	ray_dir;

	pixel_to_world(scene, &x, &y);
	ray_dir = vec3_unit(vec3_subtr(vec3_constr(x, y, -1), scene->camera.pos));
	ray = ray_constr(scene->camera.pos, ray_dir);
	return (ray);
}

/*
	We generate rays through each pixel depending on the SPP (samples per pixel).
	Then, we merge the colors of all the rays that we shot per pixel to create anti-aliasing.
*/
uint32_t	pixel_color(t_scene *scene, int x, int y)
{
	t_ray		r;
	t_color		color;
	int			i;

	color = (t_color){0};
	i = 0;
	while (i < SPP)
	{
		r = get_next_ray(scene, (double)x, (double)y);
		color = vec3_add(color, ray_color(r, scene));
		i++;
	}
	color = vec3_scale_div(color, SPP);
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}
