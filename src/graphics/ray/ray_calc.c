/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 15:17:08 by amorvai          ###   ########.fr       */
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

/*
	Determines how the light will look like on the objects using the attenuation (which is a fancy word for how bright the point is).
	We get the attenuation by finding the value of cosine the angle between the hitpoint normal and the light direction,
	which we get by dividing the dot product of the two vectors with the length of the two vectors multiplied (since the two vectors are normalize we can omit the division)
	Finally, we determine if the point is in the shadow by setting the visible boolean. Effectively turning the 
	color off or on when we multiply the point with the boolean.
*/
t_color	get_light_shade(const t_scene *scene, const t_hit_record hitpoint)
{
	t_vec3			light_vec;
	t_vec3			light_dir;
	t_ray			shadow_ray;
	double			visiblity;
	double			attenuation;
	t_color			light_color;

	light_vec = vec3_subtr(scene->light.pos, hitpoint.p);
	light_dir = vec3_scale_mult(vec3_unit(light_vec), scene->light.ratio);
	shadow_ray = ray_constr(hitpoint.p, light_dir);
	visiblity = shadow_hit(shadow_ray, scene->hittable, hitpoint, light_vec);
	attenuation = clamp_min(vec3_dot(light_dir, hitpoint.normal), 0.0);
	light_color = vec3_scale_mult(scene->light.energy, attenuation);
	return (vec3_scale_mult(light_color, visiblity));
	return (light_color);
}

/*
	Determines the shade of the object by first getting the light color and then
	mixing it with the ambient light. Finally, we multiply the color of the object
	with the light color to get our final color.
*/
t_color	shade(const t_hit_record hitpoint, const t_scene *scene)
{
	t_color			light_color;

	light_color = (t_color){0};
	if (scene->light.ratio != 0)
		light_color = get_light_shade(scene, hitpoint);
	light_color = vec3_add(scene->amb_light.energy, light_color);
	// light_color = vec3_clamp(vec3_add(scene->amb_light.energy, light_color), 0.0, 1.0);
	return (vec3_mult(hitpoint.color, light_color));
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
/* to see NORMAL-COLORS of the sides of any hittable
after:		if (world_hit())
insert:			return (vec3_scale_mult(vec3_add(hit_rec.normal, vec3_constr(1.0, 1.0, 1.0)), 0.5));
*/

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
	ray_dir = vec3_unit(vec3_constr(x, y, -1));
	ray = ray_constr(vec3_constr(0, 0, 0), ray_dir);
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
