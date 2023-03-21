/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/21 20:10:58 by jmaalouf         ###   ########.fr       */
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

static t_vec3	diffuse(t_hit_record *hit_rec)
{
	t_point3	diffuse_dir;

	diffuse_dir = vec3_add(hit_rec->p, vec3_add(hit_rec->normal, vec3_random_unit()));
	return (vec3_subtr(diffuse_dir, hit_rec->p));
}

t_vec3	luminosity(t_scene *scene, t_hit_record *hit_rec, int depth)
{
	t_color			luminance;

	luminance = vec3_scale_mult(ray_color(ray_constr(hit_rec->p, diffuse(hit_rec)), scene, depth - 1), 0.5);
	if (luminance.e[0] == 0 && luminance.e[1] == 0 && luminance.e[2] == 0)
		luminance = vec3_constr(1, 1, 1);
	return (luminance);
}

t_color	ray_color(const t_ray r, t_scene *scene, int depth)
{
	t_hit_record	hit_rec;
	// t_color			luminance;

	if (depth < 0)
		return (vec3_constr(0, 0, 0));
	hit_rec = (t_hit_record){0};
	if (world_hit(r, &hit_rec, scene->hittable))
	{
		t_color	light_clr = vec3_scale_mult(vec3_scale_div(scene->light.rgb, 255), scene->light.ratio);
		t_vec3 obj_clr = vec3_mult(light_clr, hit_rec.color);
		return (obj_clr);
	}
	return (vec3_constr(0, 0, 0));
}
/* t_color	ray_color(const t_ray r, t_scene *scene, int depth)
{
	t_hit_record	hit_rec;
	// t_color			luminance;

	if (depth < 0)
		return (vec3_constr(0, 0, 0));
	hit_rec = (t_hit_record){0};
	if (world_hit(r, &hit_rec, scene->hittable))
	{
		// t_color albedo = vec3_constr(0.18, 0.18, 0.18);
		// t_color	amb_light_clr = vec3_scale_mult(vec3_scale_div(scene->amb_light.rgb, 255), scene->amb_light.ratio);
		t_color	light_clr = vec3_scale_mult(vec3_scale_div(scene->light.rgb, 255), scene->light.ratio);

		// t_vec3 obj_clr = vec3_mult(vec3_add(amb_light_clr, light_clr), hit_rec.color);
		t_vec3 obj_clr = vec3_mult(light_clr, hit_rec.color);

		// t_vec3 light_dir = vec3_scale_mult(vec3_subtr(scene->light.pos, hit_rec.p), -1);
		
		// vec3_scale_div(albedo, PI);
		// double ratio = clamp(vec3_dot(hit_rec.normal, light_dir), 0.0, 0.999);
		// obj_clr = vec3_scale_mult(obj_clr, ratio);

		// luminance = luminosity(scene, &hit_rec, depth);
		// return (vec3_mult(luminance, obj_clr));
		return (obj_clr);
	}
	return (vec3_constr(0, 0, 0));
} */

void pixel_to_world(t_scene *scene, double *x, double *y)
{
	double px_ndc_x;
	double px_ndc_y;
	double px_screen_x;
	double px_screen_y;

	// Convert from pixels to NDC space (Normalized Device Coordinates) range (0, 1)
	px_ndc_x = (*x + 0.5) / scene->image.width;
	px_ndc_y = (*y + 0.5) / scene->image.height;

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
/* static t_ray	get_next_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	double	u;
	double	v;

	if (SPP > 1)
	{
		u = ((double)x + random_double()) / (scene->image.width - 1);
		v = ((double)y + random_double()) / (scene->image.height - 1);
	}
	else
	{
		u = (double)x / (scene->image.width - 1);
		v = (double)y / (scene->image.height - 1);
	}
	ray = ray_constr(
			scene->camera.pos,
			vec3_subtr(
				vec3_add(
					scene->image.lower_left_corner,
					vec3_add(
						vec3_scale_mult(scene->image.hori, u),
						vec3_scale_mult(scene->image.vert, v))),
				scene->camera.pos)
			);
	return (ray);
} */

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
