#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct s_camera
{
	t_point3	pos;
	t_vec3		orient;
	int			fov;
}				t_camera;

typedef struct s_amb_light
{
	double		ratio;
	t_color		rgb;
}				t_amb_light;

typedef struct s_light
{
	t_point3	pos;
	double		ratio;
	t_color		rgb;
}				t_light;

typedef struct s_sphere
{
	t_point3	pos;
	double		diameter;
	t_color		rgb;
}				t_sphere;

typedef struct s_plane
{
	t_point3	pos;
	t_vec3		orient;
	t_color		rgb;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	pos;
	t_vec3		orient;
	double		diameter;
	double		height;
	t_color		rgb;
}				t_cylinder;

typedef struct s_scene
{
	t_camera	camera;
	t_amb_light	amb_light;
	t_light		light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	bool		error;
}				t_scene;

t_scene	parse_scene(char *file);

void	populate_scene(t_scene *scene, char *file);

#endif