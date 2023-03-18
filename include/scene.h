/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:12 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/18 19:06:40 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include <stdbool.h>

# define SPP 5
# define MAX_DEPTH 1

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

typedef struct s_hittable
{
	int			sp_count;
	t_sphere	*spheres;

	int			pl_count;
	t_plane		*planes;

	int			cy_count;
	t_cylinder	*cylinders;
}				t_hittable;

typedef struct s_image
{
	double		width;
	double		height;
	double		ratio;
	double		viewport_width;
	double		viewport_height;
	double		focal_len;
	t_point3	hori;
	t_point3	vert;
	t_point3	lower_left_corner;
}				t_image;

typedef struct s_scene
{
	t_image		image;
	t_camera	camera;
	t_amb_light	amb_light;
	t_light		light;
	t_hittable	hittable;
	bool		error;
}				t_scene;

t_scene	parse(char *file);

#endif
