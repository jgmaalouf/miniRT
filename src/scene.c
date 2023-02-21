#include "scene.h"

bool	open_file(char *file, int *fd)
{
	char *extension;
	
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
	if (ft_strncmp("A", str, 1))
		if (!valid_amb_light(str))
			return (invalid_elem("ambient light"), false);
	if (ft_strncmp("C", str, 1))
		if (!valid_camera(str))
			return (invalid_elem("camera"), false);
	if (ft_strncmp("L", str, 1))
		if (!valid_light(str))
			return (invalid_elem("light"), false);
	if (ft_strncmp("sp", str, 1))
		if (!valid_sphere(str))
			return (invalid_elem("sphere"), false);
	if (ft_strncmp("pl", str, 1))
		if (!valid_plane(str))
			return (invalid_elem("plane"), false);
	if (ft_strncmp("cy", str, 1))
		if (!valid_cylinder(str))
			return (invalid_elem("cylinder"), false);
	return (true);
}

bool	valid_elem_count()
{
	if (get_count(cameras) > 1)
		return (too_much("cameras"), false);
	if (get_count(amb_lights) > 1)
		return (too_much("ambient lights"), false);
	if (get_count(lights) > 1)
		return (too_much("lights"), false);
	if (get_count(spheres) < 1)
		return (too_little("spheres"), false);
	if (get_count(planes) < 1)
		return (too_little("planes"), false);
	if (get_count(cylinders) < 1)
		return (too_little("cylinders"), false);
}

bool	scene_valid(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	if (!open_file(file, &fd))
		return (invalid_file(), false);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!valid_elem(line))
			return (close(fd), false);
		line = get_next_line(fd);
	}
	close(fd);
	if (!valid_elem_count())
		return (false);
	return (true);
}

t_scene	parse_scene(char *file)
{
	t_scene	scene;

	scene_valid(&scene, file);
	if (scene_valid(&scene, file))
		populate_scene(&scene, file);
	return (scene);
}
