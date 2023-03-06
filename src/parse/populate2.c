/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:43 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:51:49 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	fill_triple_val(char *str, t_vec3 *triple_val)
{
	ft_atod(str, &triple_val->e[0]);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	ft_atod(str, &triple_val->e[1]);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	ft_atod(str, &triple_val->e[2]);
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

void	fill_sphere(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->spheres[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->spheres[count].diameter);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->spheres[count].rgb);
	count++;
}
