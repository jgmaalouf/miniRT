/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/25 20:42:13 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h> // bool
# include <stdint.h> // uint8_t
# include <stdlib.h> // size_t
# include <float.h> // DBL_MAX
# include "scene.h"

// _____________________________________________________________________________
//
//	Definition der Elemente
// _____________________________________________________________________________

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
	{"cy",	2,	g_cylinder,		"cylinder"}
};

// _____________________________________________________________________________
//
//	Szenenvalidierung
// _____________________________________________________________________________

bool	validate_element(char *str, t_scene *scene);
void	validate_element_info(char **str, struct s_element element,
			bool *error);
bool	validate_element_count(t_scene *scene);

bool	validate_single_val(char **str, const double min, const double max);
bool	validate_triple_val(char **str, const double min, const double max);

typedef bool			(*t_valid_val)(char **, const double, const double);

static const struct s_validate
{
	uint8_t		token;
	t_valid_val	validater;
	double		min;
	double		max;
	char		*error_message;
}
p[] = {
{TOK_COORD,		validate_triple_val,	0,		0,
"%sThe coordinates for the %s are invalid!\n"},
{TOK_ORIENT,	validate_triple_val,	-1,		1,
"%sThe orientation vector for the %s is invalid!\n"},
{TOK_FOV,		validate_single_val,	0,		180,
"%sThe FOV value for the %s is invalid!\n"},
{TOK_RATIO,		validate_single_val,	0,		1,
"%sThe %s ratio is invalid!\n"},
{TOK_DIAMETER,	validate_single_val,	0,		DBL_MAX,
"%sThe %s diameter is invalid!\n"},
{TOK_HEIGHT,	validate_single_val,	0,		DBL_MAX,
"%sThe %s height is invalid!\n"},
{TOK_RGB,		validate_triple_val,	0,		255,
"%sThe RGB value for %s is invalid!\n"}
};

// _____________________________________________________________________________
//
//	Szenenfüllung
// _____________________________________________________________________________

void	fill_element(t_scene *scene, char *str);

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

// _____________________________________________________________________________
//
//	Nutzen
// _____________________________________________________________________________

void	skip_spaces(char **str);
void	increment_while_double(char **str);

void	fill_single_val(char **str, double *val);
void	fill_triple_val(char **str, t_vec3 *triple_val);

// _____________________________________________________________________________

#endif
