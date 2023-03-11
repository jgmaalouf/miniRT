/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 19:00:11 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "elem_count.h"
#include "lib.h"
#include "parse.h"
#include "scene.h"

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

void	allocate_scene_elements(t_scene *scene)
{
	scene->hittable.spheres = malloc((get_count(g_sphere, scene) + 1) * sizeof(t_sphere));
	scene->hittable.planes = malloc((get_count(g_plane, scene) + 1) * sizeof(t_plane));
	scene->hittable.cylinders = malloc((get_count(g_cylinder, scene) + 1) * sizeof(t_cylinder));
	if (scene->hittable.spheres == NULL || scene->hittable.planes == NULL
		|| scene->hittable.cylinders == NULL)
	{
		free(scene->hittable.spheres);
		free(scene->hittable.planes);
		free(scene->hittable.cylinders);
	}
}

void	scene_populate(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	allocate_scene_elements(scene);
	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	while (line != NULL)
	{
		fill_elem(scene, line);
		get_next_line(fd, &line);
	}
	close(fd);
}
