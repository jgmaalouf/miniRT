/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:11:20 by amorvai           #+#    #+#             */
/*   Updated: 2023/04/01 15:35:35 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "elem_count.h"
#include "parse.h"
#include "errors.h"

#include <stdlib.h>

// TODO: THERE SHOULD BE A MUCH CLEANER WAY OF HANDLING THE ALLOCATIONS

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
	scene->light = malloc(
			(get_count(g_light, scene) + 1) * sizeof(t_light));
	if (scene->light == NULL)
	{
		free(scene->hittable.spheres);
		free(scene->hittable.planes);
		free(scene->hittable.cylinders);
		panic_exit("bad alloc");
	}
}

void	free_scene_elements(t_scene *scene)
{
	free(scene->hittable.spheres);
	free(scene->hittable.planes);
	free(scene->hittable.cylinders);
	free(scene->light);
}
