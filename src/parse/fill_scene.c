/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 19:31:03 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "scene.h"
#include "vector.h"
#include "elem_count.h"

void	fill_light(char *str, t_scene *scene)
{
	static size_t	count;

	fill_triple_val(&str, &scene->light[count].pos);
	fill_single_val(&str, &scene->light[count].ratio);
	fill_triple_val(&str, &scene->light[count].rgb);
	scene->light[count].energy = vec3_scale_div(vec3_scale_mult(scene->light[count].rgb, scene->light[count].ratio), 255);
	count++;
}

void	fill_camera(char *str, t_scene *scene)
{
	fill_triple_val(&str, &scene->camera.pos);
	fill_triple_val(&str, &scene->camera.orient);
	scene->camera.orient = vec3_unit(scene->camera.orient);
	fill_single_val(&str, &scene->camera.fov);
}

void	fill_amb_light(char *str, t_scene *scene)
{
	fill_single_val(&str, &scene->amb_light.ratio);
	fill_triple_val(&str, &scene->amb_light.rgb);
	scene->amb_light.energy = vec3_scale_div(vec3_scale_mult(scene->amb_light.rgb, scene->amb_light.ratio), 255);
}

/* Fills scene structure with previously validated element information. Loops
through all defined elements to match the type identifier in the beginning of
the string to a defined element. Calls function to fill according part of the
scene structure with information to that element */
void	fill_element(t_scene *scene, char *str)
{
	size_t	num_elements;
	size_t	i;

	num_elements = sizeof(element) / sizeof(element[0]);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(element[i].id_str, str, element[i].id_len) == 0)
		{
			str += element[i].id_len;
			g_element_fillers[i](str, scene);
		}
		i++;
	}
}
