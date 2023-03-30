/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:38 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/30 22:11:15 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "scene.h"
#include "parse.h"
#include "errors.h"
#include "memory_alloc.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* Opens file descriptor if file format is correct. Returns 0 upon success. */
static int	open_file(char *file, int *fd)
{
	char	*extension;

	extension = ft_strnstr(file, ".rt", ft_strlen(file));
	if (extension != NULL && ft_strcmp(extension, ".rt") == 0)
	{
		*fd = open(file, O_RDONLY);
		if (*fd != -1)
			return (0);
	}
	return (1);
}

/* Checks format and content of input file line by line */
static void	scene_validate(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	size_t	i;

	if (open_file(file, &fd))
	{
		invalid_input(INVALID_FILE);
		scene->error = true;
		return ;
	}
	i = 1;
	get_next_line(fd, &line);
	while (line != NULL)
	{
		if (validate_element(line, scene, i))
			scene->error = true;
		free(line);
		get_next_line(fd, &line);
		i++;
	}
	close(fd);
	if (!validate_element_count(scene))
		scene->error = true;
}

/* Fills scene structure with content of input file line by line */
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
		free(line);
		get_next_line(fd, &line);
	}
	close(fd);
}

/* Presets and precalculates important variables */
static void	scene_image_init(t_image *img)
{
	img->width = 1280.0;
	img->height = 720.0;
	img->ratio = img->width / img->height;
}

t_scene	parse(char *file)
{
	t_scene	scene;

	scene = (t_scene){0};
	scene_validate(&scene, file);
	if (scene.error == false)
	{
		scene_populate(&scene, file);
		scene_elements_transform(&scene);
		scene_image_init(&scene.image);
		srand(time(NULL));
		scene.workers = ft_calloc(THREADS + 1, sizeof(t_worker));
		if (scene.workers == NULL)
			panic_exit("bad alloc");
	}
	return (scene);
}
