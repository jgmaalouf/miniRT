/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/04/04 22:16:29 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "elem_count.h"
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
	t_color	light_color;
	size_t	light_count;
	size_t	i;

	light_color = scene->amb_light.energy;
	light_count = get_count(g_light, scene);
	i = 0;
	while (i < light_count)
	{
		if (scene->light[i].ratio != 0)
			light_color = vec3_add(get_light_shade(scene, hitpoint, i), light_color);
		i++;
	}
	return (vec3_mult(hitpoint.color, light_color)); // Consider adding instead of multiplying
}

static t_vec3	random_dir(const t_hit_record hit_rec)
{
	return(vec3_unit(vec3_add(hit_rec.normal, vec3_random_unit())));
}

t_color	ambient_occlusion(t_scene *scene, const t_hit_record hit_rec, int depth)
{
	t_color	illum;

	illum = vec3_scale_mult(ray_color(ray_constr(hit_rec.p, random_dir(hit_rec)), scene, depth - 1), 0.5);
	if (illum.e[0] == 0 && illum.e[1] == 0 && illum.e[2] == 0)
		illum = (t_vec3){{1, 1, 1}};
	return (illum);
}

/*
	Checks if the ray hits any objects. If that's the case we shade accordingly.
	Otherwise, we return black.
*/
t_color	ray_color(const t_ray r, t_scene *scene, int depth)
{
	t_color			color;
	t_hit_record	hit_rec;

	if (depth < 0)
		return ((t_color){0});
	hit_rec = (t_hit_record){0};
	color = (t_color){0};
	if (world_hit(r, &hit_rec, scene->hittable))
	{
		color = ambient_occlusion(scene, hit_rec, depth);
		color = vec3_mult(shade(hit_rec, scene), color);
	}
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
void pixel_to_world(t_scene *scene, double *x, double *y)
{
	double px_ndc_x;
	double px_ndc_y;
	double px_screen_x;
	double px_screen_y;

	if (SPP > 1)
	{
		px_ndc_x = (*x + random_dbl(0, 1)) / scene->image.width;
		px_ndc_y = (*y + random_dbl(0, 1)) / scene->image.height;
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
	Sends a ray to the scene through the given pixel.
*/
static t_ray	get_next_ray(t_scene *scene, double x, double y)
{
	t_ray	ray;
	t_vec3	ray_dir;

	pixel_to_world(scene, &x, &y);
	ray_dir = vec3_unit(vec3_subtr(vec3_constr(x, y, -1), (t_vec3){{0, 0, 0}}));
	ray = ray_constr((t_vec3){{0, 0, 0}}, ray_dir);
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
	int			i;

	color = (t_color){0};
	i = 0;
	while (i < SPP)
	{
		r = get_next_ray(scene, (double)x, (double)y);
		color = vec3_add(color, ray_color(r, scene, MAX_DEPTH));
		i++;
	}
	color = vec3_scale_div(color, SPP);
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}