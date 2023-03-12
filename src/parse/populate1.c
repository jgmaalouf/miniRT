/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/12 19:58:46 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elem_count.h"
#include "lib.h"
#include "parse.h"
#include "scene.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	fill_light(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->light.pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->light.ratio);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->light.rgb);
}

void	fill_camera(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->camera.pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->camera.orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atoi_mod(str, &scene->camera.fov);
}

void	fill_amb_light(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	ft_atod(str, &scene->amb_light.ratio);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->amb_light.rgb);
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
