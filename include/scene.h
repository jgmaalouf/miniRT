/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:12 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 20:14:56 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "MLX42.h"

# include <stdbool.h> // bool
# include <stdint.h> // uint16_t
# include <stdlib.h> // size_t
# include <pthread.h>

# define SPP 1
# define MAX_DEPTH 1
# define THREADS 1

// _____________________________________________________________________________
//
//	Definition der Elemente
// _____________________________________________________________________________

# define TOK_COORD 0b10000000
# define TOK_ORIENT 0b1000000
# define TOK_FOV 0b100000
# define TOK_RATIO 0b10000
# define TOK_DIAMETER 0b1000
# define TOK_HEIGHT 0b100
# define TOK_ANGLE 0b10
# define TOK_RGB 0b1

// As these are static const they are not considered "global" by the norm

static const uint8_t	g_amb_light = TOK_RATIO | TOK_RGB;
static const uint8_t	g_camera = TOK_COORD | TOK_ORIENT | TOK_FOV;
static const uint8_t	g_light = TOK_COORD | TOK_RATIO | TOK_RGB;
static const uint8_t	g_sphere = TOK_COORD | TOK_DIAMETER | TOK_RGB;
static const uint8_t	g_plane = TOK_COORD | TOK_ORIENT | TOK_RGB;
static const uint8_t	g_cylinder = TOK_COORD | TOK_ORIENT
	| TOK_DIAMETER | TOK_HEIGHT | TOK_RGB;
static const uint8_t	g_cone = TOK_COORD | TOK_ORIENT
	| TOK_DIAMETER | TOK_HEIGHT | TOK_ANGLE | TOK_RGB;

static const struct s_element
{
	char		*id_str;
	size_t		id_len;
	u_int8_t	bitmask;
	char		*name;
}
element[] = {
	{"A",	1,	g_amb_light,	"ambient light"},
	{"C",	1,	g_camera,		"camera"},
	{"L",	1,	g_light,		"light"},
	{"sp",	2,	g_sphere,		"sphere"},
	{"pl",	2,	g_plane,		"plane"},
	{"cy",	2,	g_cylinder,		"cylinder"},
	{"co",	2,	g_cone,			"cone"}
};

typedef struct s_camera
{
	t_point3	pos;
	t_vec3		orient;
	double		fov;
}				t_camera;

typedef struct s_amb_light
{
	double		ratio;
	t_color		rgb;
	t_color		energy;
}				t_amb_light;

typedef struct s_light
{
	t_point3	pos;
	double		ratio;
	t_color		rgb;
	t_color		energy;
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

typedef struct s_cone
{
	t_point3	pos;
	t_vec3		orient;
	double		diameter;
	double		height;
	double		angle;
	t_color		rgb;
}				t_cone;

typedef struct s_hittable
{
	size_t		sp_count;
	t_sphere	*spheres;

	size_t		pl_count;
	t_plane		*planes;

	size_t		cy_count;
	t_cylinder	*cylinders;

	size_t		co_count;
	t_cone		*cones;
}				t_hittable;

typedef struct s_image
{
	mlx_image_t	*img;
	double		width;
	double		height;
	double		ratio;
}				t_image;

typedef struct s_worker	t_worker;

typedef struct s_scene
{
	t_image		image;
	t_camera	camera;
	t_amb_light	amb_light;
	t_light		*light;
	t_hittable	hittable;
	t_worker	*workers;
	bool		error;
}				t_scene;

typedef struct s_worker
{
	pthread_t	thread;
	size_t		start;
	size_t		end;
	t_scene		scene;
}				t_worker;

t_scene	parse(char *file);
void	transform(t_scene *scene);

#endif
