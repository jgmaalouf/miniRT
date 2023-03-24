/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 20:17:05 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "scene.h"

void	fill_light(char *str, t_scene *scene)
{
	fill_triple_val(&str, &scene->light.pos);
	fill_single_val(&str, &scene->light.ratio);
	fill_triple_val(&str, &scene->light.rgb);
}

void	fill_camera(char *str, t_scene *scene)
{
	fill_triple_val(&str, &scene->camera.pos);
	fill_triple_val(&str, &scene->camera.orient);
	fill_single_val(&str, &scene->camera.fov);
}

void	fill_amb_light(char *str, t_scene *scene)
{
	fill_single_val(&str, &scene->amb_light.ratio);
	fill_triple_val(&str, &scene->amb_light.rgb);
}

void	fill_elem(t_scene *scene, char *str)
{
	size_t	num_elements;
	size_t	i;

	num_elements = sizeof(element) / sizeof(element[0]);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(element[i].identifier, str, element[i].ident_len) == 0)
		{
			str += element[i].ident_len;
			g_element_fillers[i](str, scene);
		}
		i++;
	}
}
