/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:43 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/12 19:59:49 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parse.h"
#include "scene.h"

void	fill_cylinder(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.cylinders[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.cylinders[count].orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->hittable.cylinders[count].diameter);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->hittable.cylinders[count].height);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.cylinders[count].rgb);
	count++;
}

void	fill_plane(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.planes[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.planes[count].orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.planes[count].rgb);
	count++;
}

void	fill_sphere(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.spheres[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->hittable.spheres[count].diameter);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->hittable.spheres[count].rgb);
	count++;
}
