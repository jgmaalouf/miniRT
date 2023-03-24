/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 20:55:23 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h> // bool
# include <stdint.h> // uint8_t
# include <stdlib.h> // size_t
# include "scene.h"

# define TOK_COORD 0b1000000
# define TOK_ORIENT 0b100000
# define TOK_FOV 0b10000
# define TOK_RATIO 0b1000
# define TOK_DIAMETER 0b100
# define TOK_HEIGHT 0b10
# define TOK_RGB 0b1

// As these are static const they are not considered "global" by the norm

static const uint8_t	g_amb_light = TOK_RATIO | TOK_RGB;
static const uint8_t	g_camera = TOK_COORD | TOK_ORIENT | TOK_FOV;
static const uint8_t	g_light = TOK_COORD | TOK_RATIO | TOK_RGB;
static const uint8_t	g_sphere = TOK_COORD | TOK_DIAMETER | TOK_RGB;
static const uint8_t	g_plane = TOK_COORD | TOK_ORIENT | TOK_RGB;
static const uint8_t	g_cylinder = TOK_COORD | TOK_ORIENT
	| TOK_DIAMETER | TOK_HEIGHT | TOK_RGB;

static const struct s_element
{
	char		*identifier;
	size_t		ident_len;
	u_int8_t	bitmask;
	char		*name;
}
element[] = {
	{"A",	1,	g_amb_light,	"ambient light"},
	{"C",	1,	g_camera,		"camera"},
	{"L",	1,	g_light,		"light"},
	{"sp",	2,	g_sphere,		"sphere"},
	{"pl",	2,	g_plane,		"plane"},
	{"cy",	2,	g_cylinder,		"cylinder"}
};

// Szenenvalidierung

bool	valid_elem(char *str, t_scene *scene);
void	valid_elem_info(struct s_element element, char **str, bool *ero_bewliun);
bool	valid_elem_count(t_scene *scene);

bool	valid_coord(char **str);
bool	valid_orient(char **str);
bool	valid_fov(char **str);
bool	valid_ratio(char **str);
bool	valid_dbl_size(char **str);
bool	valid_rgb(char **str);

// typedef bool			(*t_validate)(char **str);

// Szenenfüllung

void	fill_elem(t_scene *scene, char *str);

void	fill_amb_light(char *str, t_scene *scene);
void	fill_camera(char *str, t_scene *scene);
void	fill_light(char *str, t_scene *scene);
void	fill_sphere(char *str, t_scene *scene);
void	fill_plane(char *str, t_scene *scene);
void	fill_cylinder(char *str, t_scene *scene);

typedef void			(*t_filler)(char *str, t_scene *scene);

static const t_filler	g_element_fillers[] = {
	fill_amb_light,
	fill_camera,
	fill_light,
	fill_sphere,
	fill_plane,
	fill_cylinder
};

// Nutzen

void	skip_spaces(char **str);
void	increment_while_double(char **str);

void	fill_single_val(char **str, double *val);
void	fill_triple_val(char **str, t_vec3 *triple_val);

// typedef void			(*t_scene_filler)(char **, void *);

// typedef struct s_idkyet
// {
// 	uint8_t			identifier;
// 	t_scene_filler	filler;
// 	void			*member;
// }				t_idkyet;

// static const t_idkyet	g_scene_fillers[] = {
// {TOK_COORD,		&fill_triple_val,	&(t_vec3){0}},
// {TOK_ORIENT,	&fill_triple_val,	&(t_vec3){0}},
// {TOK_FOV,		&fill_single_val,	&(double){0}},
// {TOK_RATIO,		&fill_single_val,	&(double){0}},
// {TOK_DIAMETER,	&fill_single_val,	&(double){0}},
// {TOK_HEIGHT,	&fill_single_val,	&(double){0}},
// {TOK_RGB,		&fill_triple_val,	&(t_vec3){0}}
// };

#endif
