/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:38 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/20 00:43:55 by amorvai          ###   ########.fr       */
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
#include <time.h>

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

void	scene_image_init(t_image *img, t_camera cam)
{
	img->width = 1280.0;
	img->height = 720.0;
	img->ratio = img->width / img->height;
	img->focal_len = 1.0;
	img->viewport_width = 4.0;
	img->viewport_height = img->viewport_width / img->ratio;
	img->hori = vec3_constr(img->viewport_width, 0, 0);
	img->vert = vec3_constr(0, img->viewport_height, 0);
	img->max_depth = 50;
	img->lower_left_corner
		= vec3_substr(
			cam.pos,
			vec3_add(
				vec3_scale_div(img->hori, 2),
				vec3_add(
					vec3_scale_div(img->vert, 2),
					vec3_constr(0, 0, img->focal_len)
					)
				)
			);
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
		scene_image_init(&scene.image, scene.camera);
		srand(time(NULL));
	}
	return (scene);
}
