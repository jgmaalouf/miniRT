/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:51:36 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	fill_plane(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->planes[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->planes[count].orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->planes[count].rgb);
	count++;
}

void	fill_cylinder(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->cylinders[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->cylinders[count].orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->cylinders[count].diameter);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->cylinders[count].height);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->cylinders[count].rgb);
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
	scene->spheres = malloc((get_count(spheres) + 1) * sizeof(t_sphere));
	scene->planes = malloc((get_count(planes) + 1) * sizeof(t_plane));
	scene->cylinders = malloc((get_count(cylinders) + 1) * sizeof(t_cylinder));
	if (scene->spheres == NULL || scene->planes == NULL
		|| scene->cylinders == NULL)
	{
		free(scene->spheres);
		free(scene->planes);
		free(scene->cylinders);
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
