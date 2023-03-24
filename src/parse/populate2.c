/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:43 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 17:54:33 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "scene.h"

void	fill_cylinder(char *str, t_scene *scene)
{
	static int	count;

	fill_triple_val(&str, &scene->hittable.cylinders[count].pos);
	fill_triple_val(&str, &scene->hittable.cylinders[count].orient);
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
