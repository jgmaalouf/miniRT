/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:21:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/14 14:38:08 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "utils.h"

#include <stdio.h> // printf
#include <stdlib.h> // uint_t

static t_color	ray_color(const t_ray r, t_scene *scene)
{
	t_hit_record	hit_rec;
	t_vec3			unit_direction;
	double			t;
	t_color			white;
	t_color			blue;

	white = vec3_constr(1.0, 1.0, 1.0);
	blue = vec3_constr(0.5, 0.7, 1.0);
	hit_rec = (t_hit_record){0};
	if (world_hit(r, &hit_rec, scene->hittable))
	{
		// printf("I hit something \\o/\n");
		return (vec3_scale_mult(vec3_add(hit_rec.normal, vec3_constr(1, 1, 1)), 0.5));
	}
	unit_direction = vec3_unit(r.dir);
	t = 0.5 * (unit_direction.e[1] + 1.0);
	return (
		vec3_add(
			vec3_scale_mult(white, 1.0 - t),
			vec3_scale_mult(blue, t)
		)
	);
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
		color = vec3_add(color, ray_color(r, scene));
		i++;
	}
	color = vec3_scale_div(color, SPP);
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}