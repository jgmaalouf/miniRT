/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/25 17:56:13 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "scene.h"

void	fill_light(char *str, t_scene *scene)
{
	str++;
	fill_triple_val(&str, &scene->light.pos);
	fill_single_val(&str, &scene->light.ratio);
	fill_triple_val(&str, &scene->light.rgb);
	scene->light.energy = vec3_scale_div(vec3_scale_mult(scene->light.rgb, scene->light.ratio), 255);
}

void	fill_camera(char *str, t_scene *scene)
{
	str++;
	fill_triple_val(&str, &scene->camera.pos);
	fill_triple_val(&str, &scene->camera.orient);
	fill_single_val(&str, &scene->camera.fov);
}

void	fill_amb_light(char *str, t_scene *scene)
{
	str++;
	fill_single_val(&str, &scene->amb_light.ratio);
	fill_triple_val(&str, &scene->amb_light.rgb);
	scene->amb_light.energy = vec3_scale_div(vec3_scale_mult(scene->amb_light.rgb, scene->amb_light.ratio), 255);
}

void	fill_elem(t_scene *scene, char *str)
{
	size_t	num_fillers = sizeof(filler) / sizeof(filler[0]);
	size_t	i;

	i = 0;
	while (i < num_fillers)
	{
		if (ft_strncmp(filler[i].elem, str, filler[i].elem_len) == 0)
			filler[i].filler(str, scene);
		i++;
	}
}
