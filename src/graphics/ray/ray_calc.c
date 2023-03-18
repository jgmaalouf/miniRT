/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/18 20:03:09 by jmaalouf         ###   ########.fr       */
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

t_vec3	scatter(t_hit_record hit_rec)
{
	t_point3	scatter_dir;

	scatter_dir = vec3_add(hit_rec.p, vec3_add(hit_rec.normal, vec3_random_unit()));
	return (vec3_substr(scatter_dir, hit_rec.p));
}

static t_color	ray_color(const t_ray r, t_scene *scene, int depth)
{
	t_hit_record	hit_rec;
	// t_color			ray_clr;

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

		t_vec3 light_dir = vec3_scale_mult(vec3_substr(scene->light.pos, hit_rec.p), -1);
		
		// vec3_scale_div(albedo, PI);
		double ratio = clamp(vec3_dot(hit_rec.normal, light_dir), 0.0, 0.999);
		obj_clr = vec3_scale_mult(obj_clr, ratio);

		// ray_clr = ray_color(ray_constr(hit_rec.p, scatter(hit_rec)), scene, depth - 1);
		// if (ray_clr.e[0] == 0 && ray_clr.e[1] == 0 && ray_clr.e[2] == 0)
		// 	ray_clr = vec3_add(ray_clr, vec3_constr(1, 1, 1));
		// return (vec3_mult(ray_clr, obj_clr));
		return (obj_clr);
	}
	return (vec3_constr(0, 0, 0));
}

static t_ray	get_next_ray(int x, int y, t_image img, t_camera cam)
{
	t_ray	ray;
	double	u;
	double	v;

	if (SPP > 1)
	{
		u = ((double)x + random_double()) / (img.width - 1);
		v = ((double)y + random_double()) / (img.height - 1);
	}
	else
	{
		u = (double)x / (img.width - 1);
		v = (double)y / (img.height - 1);
	}
	// printf("x:\t%i,\ty:\t%i\n", x, y);
	ray = ray_constr(
			cam.pos,
			vec3_substr(
				vec3_add(
					img.lower_left_corner,
					vec3_add(
						vec3_scale_mult(img.hori, u),
						vec3_scale_mult(img.vert, v))),
				cam.pos)
			);
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
		r = get_next_ray(scene->image.width - x, scene->image.height - y,
				scene->image, scene->camera);
		color = vec3_add(color, ray_color(r, scene, MAX_DEPTH));
		i++;
	}
	color = vec3_scale_div(color, SPP);
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}
