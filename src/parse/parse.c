/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:38 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:51:05 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	open_file(char *file, int *fd)
{
	char	*extension;

	extension = ft_strnstr(file, ".rt", ft_strlen(file));
	if (extension != NULL && ft_strcmp(extension, ".rt") == 0)
	{
		*fd = open(file, O_RDONLY);
		if (*fd != -1)
			return (true);
	}
	return (false);
}

bool	valid_elem(char *str)
{
	if (ft_strncmp("A", str, 1) == 0 && ft_isspace(*(str + 1)))
		return (valid_amb_light(str));
	if (ft_strncmp("C", str, 1) == 0 && ft_isspace(*(str + 1)))
		return (valid_camera(str));
	if (ft_strncmp("L", str, 1) == 0 && ft_isspace(*(str + 1)))
		return (valid_light(str));
	if (ft_strncmp("sp", str, 2) == 0 && ft_isspace(*(str + 2)))
		return (valid_sphere(str));
	if (ft_strncmp("pl", str, 2) == 0 && ft_isspace(*(str + 2)))
		return (valid_plane(str));
	if (ft_strncmp("cy", str, 2) == 0 && ft_isspace(*(str + 2)))
		return (valid_cylinder(str));
	if (ft_strncmp("\n", str, 1) == 0)
		return (true);
	return (inval_arg(UNKNOWN, "element"));
}

bool	valid_elem_count(void)
{
	if (get_count(cameras) > 1)
		return (inval_amount(MORE, "cameras"), false);
	if (get_count(cameras) < 1)
		return (inval_amount(LESS, "cameras"), false);
	if (get_count(amb_lights) > 1)
		return (inval_amount(MORE, "ambient lights"), false);
	if (get_count(amb_lights) < 1)
		return (inval_amount(LESS, "ambient lights"), false);
	if (get_count(lights) > 1)
		return (inval_amount(MORE, "lights"), false);
	if (get_count(lights) < 1)
		return (inval_amount(LESS, "lights"), false);
	if (get_count(spheres) < 1
		&& get_count(planes) < 1
		&& get_count(cylinders) < 1)
		return (inval_amount(LESS, "elements"), false);
	return (true);
}

bool	scene_valid(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	if (!open_file(file, &fd))
		return (inval_input(INVALID_FILE), scene->error = true, false);
	get_next_line(fd, &line);
	while (line != NULL)
	{
		if (!valid_elem(line))
			return (close(fd), scene->error = true, false);
		get_next_line(fd, &line);
	}
	close(fd);
	if (!valid_elem_count())
		return (scene->error = true, false);
	return (true);
}

t_scene	parse(char *file)
{
	t_scene	scene;

	scene.error = false;
	if (scene_valid(&scene, file))
		scene_populate(&scene, file);
	return (scene);
}
