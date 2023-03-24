/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 17:08:56 by amorvai          ###   ########.fr       */
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
}

void	fill_elem(t_scene *scene, char *str)
{
	if (ft_strncmp("A", str, 1) == 0)
		return (fill_amb_light(str, scene));
	if (ft_strncmp("C", str, 1) == 0)
		return (fill_camera(str, scene));
	if (ft_strncmp("L", str, 1) == 0)
		return (fill_light(str, scene));
	if (ft_strncmp("sp", str, 2) == 0)
		return (fill_sphere(str, scene));
	if (ft_strncmp("pl", str, 2) == 0)
		return (fill_plane(str, scene));
	if (ft_strncmp("cy", str, 2) == 0)
		return (fill_cylinder(str, scene));
}


// void	fill_elem(t_scene *scene, char *str)
// {
// 	size_t	num_fillers = sizeof(filler) / sizeof(filler[0]);
// 	size_t	i;

// 	i = 0;
// 	while (i < num_fillers)
// 	{
// 		if (ft_strncmp(filler[i].elem, str, filler[i].elem_len))
// 			filler[i].filler(str, scene);
// 		i++;
// 	}
// }
