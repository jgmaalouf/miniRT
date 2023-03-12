/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:38 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/12 19:57:45 by amorvai          ###   ########.fr       */
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

void	allocate_scene_elements(t_scene *scene)
{
	scene->hittable.spheres = malloc((get_count(g_sphere, scene) + 1) * sizeof(t_sphere));
	scene->hittable.planes = malloc((get_count(g_plane, scene) + 1) * sizeof(t_plane));
	scene->hittable.cylinders = malloc((get_count(g_cylinder, scene) + 1) * sizeof(t_cylinder));
	if (scene->hittable.spheres == NULL || scene->hittable.planes == NULL
		|| scene->hittable.cylinders == NULL) // this is problematic because trying to free whatever is not allocated will result in error
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
		get_next_line(fd, &line); // line needs to be freed before next call
	}
	close(fd);
}

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
		get_next_line(fd, &line); // line needs to be freed before next call
	}
	close(fd);
	if (!valid_elem_count(scene))
		scene->error = true;
}

// void	scene_init(t_scene *scene)
// {
// 	scene->error = false;
// 	scene->hittable.sp_count = 0;
// 	scene->hittable.pl_count = 0;
// 	scene->hittable.cy_count = 0;
// }

t_scene	parse(char *file)
{
	t_scene	scene;

	// scene_init(&scene);
	scene = (t_scene){0};
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
