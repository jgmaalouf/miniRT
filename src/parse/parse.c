/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:38 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/25 22:10:44 by amorvai          ###   ########.fr       */
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

static void	scene_elements_allocate(t_scene *scene)
{
	scene->hittable.spheres = malloc(
			(get_count(g_sphere, scene) + 1) * sizeof(t_sphere));
	if (scene->hittable.spheres == NULL)
		panic_exit("bad alloc");
	scene->hittable.planes = malloc(
			(get_count(g_plane, scene) + 1) * sizeof(t_plane));
	if (scene->hittable.planes == NULL)
	{
		free(scene->hittable.spheres);
		panic_exit("bad alloc");
	}
	scene->hittable.cylinders = malloc(
			(get_count(g_cylinder, scene) + 1) * sizeof(t_cylinder));
	if (scene->hittable.cylinders == NULL)
	{
		free(scene->hittable.spheres);
		free(scene->hittable.planes);
		panic_exit("bad alloc");
	}
}

static void	scene_populate(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	scene_elements_allocate(scene);
	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	while (line != NULL)
	{
		fill_element(scene, line);
		get_next_line(fd, &line);
		free(line);
	}
	close(fd);
}

static bool	open_file(char *file, int *fd)
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

static void	scene_validate(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	size_t	i;

	if (!open_file(file, &fd))
	{
		inval_input(INVALID_FILE);
		scene->error = true;
		return ;
	}
	i = 0;
	get_next_line(fd, &line);
	while (line != NULL)
	{
		if (validate_element(line, scene, i))
			scene->error = true;
		get_next_line(fd, &line);
		free(line);
		i++;
	}
	close(fd);
	if (!validate_element_count(scene))
		scene->error = true;
}

static void	scene_image_init(t_image *img, t_camera cam)
{
	img->width = 1280.0;
	img->height = 720.0;
	img->ratio = img->width / img->height;
	img->focal_len = 1.0;
	img->viewport_width = 4.0;
	img->viewport_height = img->viewport_width / img->ratio;
	img->hori = vec3_constr(img->viewport_width, 0, 0);
	img->vert = vec3_constr(0, img->viewport_height, 0);
	img->max_depth = 1;
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

t_scene	parse(char *file)
{
	t_scene	scene;

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
