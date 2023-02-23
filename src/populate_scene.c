#include "scene.h"

void	fill_triple_val(char *str, t_vec3 *triple_val)
{
	triple_val->e[0] = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	triple_val->e[1] = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	triple_val->e[2] = ft_atod(str);
}

void	fill_amb_light(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	scene->amb_light.ratio = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->amb_light.rgb);
}

void	fill_camera(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->camera.pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->camera.orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atoi(str, &scene->camera.fov);
}

void	fill_light(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->light.pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	scene->light.ratio = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->light.rgb);
}

void	fill_sphere(char *str, t_scene *scene)
{
	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->spheres[get_count(spheres)].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	scene->spheres[get_count(spheres)].diameter = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->spheres[get_count(spheres)].rgb);
	decr_count(spheres);
}

void	fill_plane(char *str, t_scene *scene)
{
	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->planes[get_count(planes)].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->planes[get_count(planes)].orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->planes[get_count(planes)].rgb);
	decr_count(planes);
}

void	fill_cylinder(char *str, t_scene *scene)
{
	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->cylinders[get_count(cylinders)].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->cylinders[get_count(cylinders)].orient);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == ',')
		str++;
	skip_spaces(&str);
	scene->cylinders[get_count(cylinders)].diameter = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	scene->cylinders[get_count(cylinders)].height = ft_atod(str);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	fill_triple_val(str, &scene->cylinders[get_count(cylinders)].rgb);
	decr_count(cylinders);
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
	scene->spheres = ft_calloc(get_count(spheres) + 1, sizeof(t_sphere));
	scene->planes = ft_calloc(get_count(planes) + 1, sizeof(t_plane));
	scene->cylinders = ft_calloc(get_count(cylinders) + 1, sizeof(t_cylinder));
	if (scene->spheres == NULL || scene->planes == NULL
		|| scene->cylinders == NULL)
	{
		free(scene->spheres);
		free(scene->planes);
		free(scene->cylinders);
	}
}

void populate_scene(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	allocate_scene_elements(scene);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_elem(scene, line);
		line = get_next_line(fd);
	}
	close(fd);
}
