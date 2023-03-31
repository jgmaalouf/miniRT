/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:11:20 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 19:35:54 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "elem_count.h"
#include "parse.h"
#include "errors.h"

#include <stdlib.h>

static void	scene_elements_allocate2(t_scene *scene)
{
	scene->hittable.cones = malloc(
			(get_count(g_cone, scene) + 1) * sizeof(t_cone));
	if (scene->hittable.cones == NULL)
	{
		free(scene->hittable.cylinders);
		free(scene->hittable.spheres);
		free(scene->hittable.planes);
		panic_exit("bad alloc");
	}
	scene->light = malloc(
			(get_count(g_light, scene) + 1) * sizeof(t_light));
	if (scene->light == NULL)
	{
		free(scene->hittable.cones);
		free(scene->hittable.cylinders);
		free(scene->hittable.spheres);
		free(scene->hittable.planes);
		panic_exit("bad alloc");
	}
}

void	scene_elements_allocate(t_scene *scene)
{
	scene->hittable.spheres = malloc(
			(get_count(g_sphere, scene) + 1) * sizeof(t_sphere));
	if (scene->hittable.spheres == NULL)
		panic_exit("bad alloc");
	scene->hittable.planes = malloc(
			(get_count(g_plane, scene) + 1) * sizeof(t_plane));
	if (scene->hittable.planes == NULL)
	{
		free(scene->hittable.spheres);
		panic_exit("bad alloc");
	}
	scene->hittable.cylinders = malloc(
			(get_count(g_cylinder, scene) + 1) * sizeof(t_cylinder));
	if (scene->hittable.cylinders == NULL)
	{
		free(scene->hittable.spheres);
		free(scene->hittable.planes);
		panic_exit("bad alloc");
	}
	scene_elements_allocate2(scene);
}

void	free_scene_elements(t_scene *scene)
{
	free(scene->hittable.spheres);
	free(scene->hittable.planes);
	free(scene->hittable.cylinders);
	free(scene->hittable.cones);
	free(scene->light);
}
