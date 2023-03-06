#include "scene.h"

void	fill_triple_val(char *str, t_vec3 *triple_val)
{
	ft_atod(str, &triple_val->e[0]);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	ft_atod(str, &triple_val->e[1]);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	ft_atod(str, &triple_val->e[2]);
}

void	fill_amb_light(char *str, t_scene *scene)
{
	str++;
	skip_spaces(&str);
	ft_atod(str, &scene->amb_light.ratio);
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
	ft_atod(str, &scene->light.ratio);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->light.rgb);
}

void	fill_sphere(char *str, t_scene *scene)
{
	static int	count;

	str += 2;
	skip_spaces(&str);
	fill_triple_val(str, &scene->spheres[count].pos);
	while (ft_isdigit(*str) || *str == '.' || *str == '+'
		|| *str == '-' || *str == ',')
		str++;
	skip_spaces(&str);
	ft_atod(str, &scene->spheres[count].diameter);
	while (ft_isdigit(*str) || *str == '.' || *str == '+')
		str++;
	skip_spaces(&str);
	fill_triple_val(str, &scene->spheres[count].rgb);
	count++;
}

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
