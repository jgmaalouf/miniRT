/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:38 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 21:22:09 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "elem_count.h"
#include "scene.h"
#include "parse.h"
#include "errors.h"

#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

bool	valid_elem(char *str, t_scene *scene)
{
	uint8_t	elem_type;
	bool	ero_bewliun;

	ero_bewliun = true;
	elem_type = 0;
	if (ft_strncmp("A", str, 1) == 0 && ft_isspace(*(str += 1)))
		elem_type = g_amb_light;
	else if (ft_strncmp("C", str, 1) == 0 && ft_isspace(*(str += 1)))
		elem_type = g_camera;
	else if (ft_strncmp("L", str, 1) == 0 && ft_isspace(*(str += 1)))
		elem_type = g_light;
	else if (ft_strncmp("sp", str, 2) == 0 && ft_isspace(*(str += 2)))
		elem_type = g_sphere;
	else if (ft_strncmp("pl", str, 2) == 0 && ft_isspace(*(str += 2)))
		elem_type = g_plane;
	else if (ft_strncmp("cy", str, 2) == 0 && ft_isspace(*(str += 2)))
		elem_type = g_cylinder;
	valid_elem_info(elem_type, &str, &ero_bewliun);
	if (!ft_strchr("\n#", *str))
		inval_arg((uint8_t)0, elem_type);
	incr_count(elem_type, scene);
	return (ero_bewliun);
}


bool	valid_elem_count(t_scene *scene)
{
	bool	err;

	err = true;
	if (get_count(g_camera, scene) > 1)
		err = inval_amount(MORE, "cameras");
	if (get_count(g_camera, scene) < 1)
		err = inval_amount(LESS, "cameras");
	if (get_count(g_amb_light, scene) > 1)
		err = inval_amount(MORE, "ambient lights");
	if (get_count(g_amb_light, scene) < 1)
		err = inval_amount(LESS, "ambient lights");
	if (get_count(g_light, scene) > 1)
		err = inval_amount(MORE, "lights");
	if (get_count(g_light, scene) < 1)
		err = inval_amount(LESS, "lights");
	return (err);
}

void	scene_validate(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	if (!open_file(file, &fd))
	{
		inval_input(INVALID_FILE);
		scene->error = true;
		return ;
	}
	get_next_line(fd, &line);
	while (line != NULL)
	{
		if (!valid_elem(line, scene))
			scene->error = true;
		get_next_line(fd, &line);
	}
	close(fd);
	if (!valid_elem_count(scene))
		scene->error = true;
}

void	scene_init(t_scene *scene)
{
	scene->error = false;
	scene->hittable.sp_count = 0;
	scene->hittable.pl_count = 0;
	scene->hittable.cy_count = 0;
}

t_scene	parse(char *file)
{
	t_scene	scene;

	scene_init(&scene);
	scene_validate(&scene, file);
	if (scene.error == false)
	{
		scene_populate(&scene, file);
		scene.image.focal_len = 1.0;
		scene.image.width = 1920.0;
		scene.image.height = 1080.0;
		scene.image.ratio = scene.image.width / scene.image.height;
	}
	return (scene);
}
