/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 21:37:56 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "graphics.h"
#include "hittable.h"
#include "utils.h"

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

/*
	Converts the pixel into something that the camera can shoot
	rays through in 3 steps.
		1. Convert from pixels to NDC space
			(Normalized Device Coordinates) range (0, 1).
		2. Convert from NDC space to screen space range (-1, 1).
		3. Convert from screen space to camera space.
*/
void	pixel_to_world(t_scene *scene, double *x, double *y)
{
	double	px_ndc_x;
	double	px_ndc_y;
	double	px_screen_x;
	double	px_screen_y;

	px_ndc_x = (*x + 0.5) / scene->image.width;
	px_ndc_y = (*y + 0.5) / scene->image.height;
	px_screen_x = 2 * px_ndc_x - 1;
	px_screen_y = 1 - 2 * px_ndc_y;
	*x = px_screen_x * scene->image.ratio
		* tan(((double)scene->camera.fov * (M_PI / 180.0)) / 2.0);
	*y = px_screen_y
		* tan(((double)scene->camera.fov * (M_PI / 180.0)) / 2.0);
}

/*
	Sends a ray to the scene through the given pixel.
*/
static t_ray	get_next_ray(t_scene *scene, double x, double y)
{
	t_ray	ray;
	t_vec3	ray_dir;

	pixel_to_world(scene, &x, &y);
	ray_dir = vec3_unit(vec3_subtr(vec3_constr(x, y, -1), vec3_constr(0, 0, 0)));
	ray = ray_constr(vec3_constr(0, 0, 0), ray_dir);
	return (ray);
}

/*
	We generate rays through each pixel.
	Then, we find the color of the ray that we shot.
*/
uint32_t	pixel_color(t_scene *scene, int x, int y)
{
	t_ray		r;
	t_color		color;

	r = get_next_ray(scene, (double)x, (double)y);
	color = ray_color(r, scene);
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}
