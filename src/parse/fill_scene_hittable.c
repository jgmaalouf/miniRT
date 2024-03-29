/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene_hittable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:43 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/30 01:20:11 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "scene.h"
#include "vector.h"
#include <math.h>

void	fill_cylinder(char *str, t_scene *scene)
{
	static int	count;

	fill_triple_val(&str, &scene->hittable.cylinders[count].pos);
	if (vec3_length(scene->hittable.cylinders[count].pos)
		== fabs(scene->hittable.cylinders[count].pos.e[2]))
		scene->hittable.cylinders[count].pos.e[1] = 0.00001;
	fill_triple_val(&str, &scene->hittable.cylinders[count].orient);
	scene->hittable.cylinders[count].orient
		= vec3_unit(scene->hittable.cylinders[count].orient);
	fill_single_val(&str, &scene->hittable.cylinders[count].diameter);
	fill_single_val(&str, &scene->hittable.cylinders[count].height);
	fill_triple_val(&str, &scene->hittable.cylinders[count].rgb);
	count++;
}

void	fill_plane(char *str, t_scene *scene)
{
	static int	count;

	fill_triple_val(&str, &scene->hittable.planes[count].pos);
	fill_triple_val(&str, &scene->hittable.planes[count].orient);
	scene->hittable.planes[count].orient
		= vec3_unit(scene->hittable.planes[count].orient);
	fill_triple_val(&str, &scene->hittable.planes[count].rgb);
	count++;
}

void	fill_sphere(char *str, t_scene *scene)
{
	static int	count;

	fill_triple_val(&str, &scene->hittable.spheres[count].pos);
	fill_single_val(&str, &scene->hittable.spheres[count].diameter);
	fill_triple_val(&str, &scene->hittable.spheres[count].rgb);
	count++;
}
