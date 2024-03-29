/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:45:38 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 00:53:13 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "transform.h"

#include <stdlib.h>

void	transform_light(t_scene *scene, double w_to_c[4][4])
{
	transform_point(&scene->light.pos, w_to_c);
}

void	transform_hittable_sphere(t_scene *scene, double w_to_c[4][4])
{
	size_t	i;

	i = 0;
	while (i < scene->hittable.sp_count)
	{
		transform_point(&scene->hittable.spheres[i].pos, w_to_c);
		i++;
	}
}

void	transform_hittable_plane(t_scene *scene, double w_to_c[4][4])
{
	size_t	i;

	i = 0;
	while (i < scene->hittable.pl_count)
	{
		transform_point(&scene->hittable.planes[i].pos, w_to_c);
		transform_vector(&scene->hittable.planes[i].orient, w_to_c);
		i++;
	}
}

void	transform_hittable_cylinder(t_scene *scene, double w_to_c[4][4])
{
	size_t	i;

	i = 0;
	while (i < scene->hittable.cy_count)
	{
		transform_point(&scene->hittable.cylinders[i].pos, w_to_c);
		transform_vector(&scene->hittable.cylinders[i].orient, w_to_c);
		i++;
	}
}
