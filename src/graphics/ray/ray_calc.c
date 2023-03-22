/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/22 17:09:05 by jmaalouf         ###   ########.fr       */
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

#define PI (double)3.14

t_color	ray_color(const t_ray r, t_scene *scene, int depth);

static t_vec3	random_dir(const t_hit_record hit_rec)
{
	t_vec3	random_dir;

	random_dir = vec3_add(hit_rec.p, vec3_add(hit_rec.normal, vec3_random_unit()));
	return (vec3_subtr(random_dir, hit_rec.p));
}

t_color	luminosity(t_scene *scene, const t_hit_record hit_rec, int depth)
{
	t_color	luminance;

	luminance = vec3_scale_mult(ray_color(ray_constr(hit_rec.p, random_dir(hit_rec)), scene, depth - 1), 0.5);
	if (luminance.e[0] == 0 && luminance.e[1] == 0 && luminance.e[2] == 0)
		luminance = vec3_constr(0.1, 0.1, 0.1);
	return (luminance);
}

static const t_color black = (t_color){0};
// static const t_color white = (t_color){1, 1, 1};

t_color	ray_color(const t_ray r, t_scene *scene, int depth)
{
	t_hit_record	hit_rec;
	t_hit_record	shadow_rec;
	t_color			luminance;
	t_color			light_clr;

	if (depth < 0)
		return (black);
	light_clr = vec3_scale_mult(vec3_scale_div(scene->light.rgb, 256), scene->light.ratio);
	hit_rec = (t_hit_record){0};
	if (world_hit(r, &hit_rec, scene->hittable))
	{
		t_vec3	light_dir = vec3_subtr(scene->light.pos, hit_rec.p);
		t_ray shadow_ray = ray_constr(hit_rec.p, light_dir);
		luminance = luminosity(scene, hit_rec, depth);
		if (world_hit(shadow_ray, &shadow_rec, scene->hittable))
			return (black);
		double	d = clamp(vec3_dot(hit_rec.normal, light_dir), 0.0, 1.0); // cos(angle)
		t_vec3 obj_clr = vec3_scale_mult(vec3_mult(light_clr, hit_rec.color), d);
		obj_clr = vec3_mult(obj_clr, luminance);
		return (obj_clr);
	}
	return (black);
}

void pixel_to_world(t_scene *scene, double *x, double *y)
{
	double px_ndc_x;
	double px_ndc_y;
	double px_screen_x;
	double px_screen_y;

	if (SPP > 1)
	{
		// Convert from pixels to NDC space (Normalized Device Coordinates) range (0, 1)
		px_ndc_x = (*x + random_double_in(0, 1)) / scene->image.width;
		px_ndc_y = (*y + random_double_in(0, 1)) / scene->image.height;
	}
	else
	{
		// Convert from pixels to NDC space (Normalized Device Coordinates) range (0, 1)
		px_ndc_x = (*x + 0.5) / scene->image.width;
		px_ndc_y = (*y + 0.5) / scene->image.height;
	}

	// Convert from NDC space to screen space range (-1, 1)
	px_screen_x = 2 * px_ndc_x - 1;
	px_screen_y = 1 - 2 * px_ndc_y;

	// Convert from screen space to camera space
	*x  = px_screen_x * scene->image.ratio * tan(((double)scene->camera.fov * (M_PI / 180.0)) / 2.0);
	*y  = px_screen_y * tan(((double)scene->camera.fov * (M_PI / 180.0)) / 2.0);
}

static t_ray	get_next_ray(t_scene *scene, double x, double y)
{
	t_ray	ray;
	t_vec3	ray_dir;

	pixel_to_world(scene, &x, &y);
	ray_dir = vec3_unit(vec3_subtr(vec3_constr(x, y, -1), scene->camera.pos));
	ray = ray_constr(scene->camera.pos, ray_dir);
	return (ray);
}

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
		// color = vec3_add(vec3_scale_div(color, SPP), ray_color(r, scene, MAX_DEPTH));
		i++;
	}
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}
