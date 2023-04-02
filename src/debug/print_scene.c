/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:40:45 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/01 15:33:38 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "elem_count.h"
#include "debug.h"
#include "parse.h"
#include "scene.h"

static void	print_amb_and_cam_and_light(t_scene scene)
{
	size_t	i;

	printf("A\t%.1f\t\t\t\t\t\t\t%.1f,%.1f,%.1f\n\n",
		scene.amb_light.ratio,
		scene.amb_light.rgb.e[0],
		scene.amb_light.rgb.e[1],
		scene.amb_light.rgb.e[2]);
	printf("C\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\n\n",
		scene.camera.pos.e[0],
		scene.camera.pos.e[1],
		scene.camera.pos.e[2],
		scene.camera.orient.e[0],
		scene.camera.orient.e[1],
		scene.camera.orient.e[2],
		scene.camera.fov);
	i = 0;
	while (i < get_count(g_light, &scene))
	{
		printf("L\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n",
			scene.light[i].pos.e[0], scene.light[i].pos.e[1],
			scene.light[i].pos.e[2], scene.light[i].ratio,
			scene.light[i].rgb.e[0], scene.light[i].rgb.e[1],
			scene.light[i].rgb.e[2]);
		i++;
	}
}

static void	print_plane(t_scene scene)
{
	size_t	i;

	i = 0;
	while (i < get_count(g_plane, &scene))
	{
		printf("pl\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t\t\t%.1f,%.1f,%.1f\n\n",
			scene.hittable.planes[i].pos.e[0],
			scene.hittable.planes[i].pos.e[1],
			scene.hittable.planes[i].pos.e[2],
			scene.hittable.planes[i].orient.e[0],
			scene.hittable.planes[i].orient.e[1],
			scene.hittable.planes[i].orient.e[2],
			scene.hittable.planes[i].rgb.e[0],
			scene.hittable.planes[i].rgb.e[1],
			scene.hittable.planes[i].rgb.e[2]);
		i++;
	}
}

static void	print_sphere(t_scene scene)
{
	size_t	i;

	i = 0;
	while (i < get_count(g_sphere, &scene))
	{
		printf("sp\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n",
			scene.hittable.spheres[i].pos.e[0],
			scene.hittable.spheres[i].pos.e[1],
			scene.hittable.spheres[i].pos.e[2],
			scene.hittable.spheres[i].diameter,
			scene.hittable.spheres[i].rgb.e[0],
			scene.hittable.spheres[i].rgb.e[1],
			scene.hittable.spheres[i].rgb.e[2]);
		i++;
	}
}

static void	print_cylinder(t_scene scene)
{
	size_t	i;

	i = 0;
	while (i < get_count(g_cylinder, &scene))
	{
		printf("cy\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%.1f,%.1f,%.1f\n\n",
			scene.hittable.cylinders[i].pos.e[0],
			scene.hittable.cylinders[i].pos.e[1],
			scene.hittable.cylinders[i].pos.e[2],
			scene.hittable.cylinders[i].orient.e[0],
			scene.hittable.cylinders[i].orient.e[1],
			scene.hittable.cylinders[i].orient.e[2],
			scene.hittable.cylinders[i].diameter,
			scene.hittable.cylinders[i].height,
			scene.hittable.cylinders[i].rgb.e[0],
			scene.hittable.cylinders[i].rgb.e[1],
			scene.hittable.cylinders[i].rgb.e[2]);
		i++;
	}
}

void	print_scene(t_scene scene)
{
	print_amb_and_cam_and_light(scene);
	print_sphere(scene);
	print_plane(scene);
	print_cylinder(scene);
}
